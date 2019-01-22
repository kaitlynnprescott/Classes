import math
import operator
import random
from PIL import Image, ImageDraw, ImageColor

SOBEL_MAGNITUDE = 40

############################
## Define Gaussian Kernel ##
############################

def gauss_kernel(sigma):
    '''
    Parameters: sigma
    returns: gaussian filter

    '''
    # initialize kernel and sum
    kernel = [[0,0,0],[0,0,0],[0,0,0]]
    ksum = 0
    # calculate the gaussian filter based on the sigma and filter size given.
    for x in range(3):
        xsq = x**2
        for y in range(3):
            ysq = y**2
            twosigma = 2.0*(sigma**2)
            twopisigma = 1.0*(twosigma*math.pi)
            pwr = -1*(xsq+ysq)/twosigma
            kernel[x][y] = math.e*pwr*twopisigma
            ksum += kernel[x][y]
    mult = 10/ksum
    for x in range(3):
        for y in range(3):
            kernel[x][y] *= mult
    return kernel

#########################################
## Combine Sobel filters to one image. ##
#########################################

def mysobel(sobel_x, sobel_y):
    '''
    Parameters: sobel_x - x direction sobel filtered image
                sobel_y - y direction sobel filtered image
    returns: (intensity, angle) - sobel filtered image, consisting of
                both x and y directions -> intensity and angle matrices

    '''
    # combine sobel filterer images into one image
    intensity = []
    angle = []
    for x in range(len(sobel_x)):
        ir = []
        ar = []
        for y in range(len(sobel_x[0])):
            xs = sobel_x[x][y]
            ys = sobel_y[x][y]
            mag = math.sqrt((xs**2) + (ys**2))  
            ir.append(int(mag))
            if ys == 0:
                value = -1
            else:
                value = math.atan(xs/ys)
            if value < (-1 * math.pi)/4:
                ar.append(-2)
            elif value < 0:
                ar.append(-1)
            elif value < math.pi / 4:
                ar.append(1)
            else:
                ar.append(2)
        intensity.append(ir)
        ir = []
        angle.append(ar)
        ar = []
    return (intensity, angle)


#################################
## Perform Hessian Suppression ##
#################################

def hess_suppress(sobel):
    '''
    Parameters: sobel - the intensity and angle matrices from running mysobel
    returns: im - hessian suppressed image in matrix form

    '''
    intensity = sobel[0]
    angle = sobel[1]
    row = len(intensity)
    col = len(intensity[0])
    im = [[0] * col] # pad array with 0s (top) 
    for r in range(1, row-1):
        curr = [0] # pad array with 0s (left)
        for c in range(1, col-1):
            i = intensity[r][c]
            a = angle[r][c]
            # vertical line
            if a == 2 or a == -2:
                comp = [intensity[r-1][c], intensity[r+1][c]]
            # horizontal
            elif a == 1 or a == -1:
                comp = [intensity[r][c-1], intensity[r][c+1]]
            # if i is the max, set it to 255 (white), otherwise, set it to black
            if i > max(comp):
                curr.append(255)
            else:
                curr.append(0)
        curr.append(0) # pad array with 0s (right)
        im.append(curr)
    im.append([0] * len(intensity[0])) # pad array with 0s (bottom)
    return im

def hess_thresh(matrix, threshold):
    '''
    Parameters: matrix - the image matrix to threshold
                threshold - the desired threshold for the hessian image.
    returns: newim - an image (matrix form) that is thresholded for
                for hessian suppression

    '''
    newim = matrix
    for x in range(len(matrix[0])):
        for y in range(len(matrix)):
            # if the image is greater than the threshold, set it to white
            # otherwise, set it to black
            if newim[y][x] > threshold:
                newim[y][x] = 255
            else:
                newim[y][x] = 0
    return newim
#######################################
## Compute distance between 2 points ##
#######################################

def dist(x, y):
    '''
    Parameters: x, y - two points
    returns: distance between the points

    '''
    return math.sqrt((x[0] - y[0])**2 + (x[1] - y[1])**2)

####################################
## Check if a point is an inlier. ##
####################################

def isinlier(x, y, z):
    '''
    Parameters: x, y, z
    returns: whether z is between x and y
    '''
    xz = dist(x,z)
    zy = dist(z,y)
    xy = dist(x,y)
    a = xz + zy <= 1.001 * xy
    b = xz + zy >= xy
    return a and b

######################################
## Perform RANSAC to fit best lines ##
######################################

def ransac(features, numit):
    '''
    Parameters: features - set of points to run ransac on
                numit - the number of iterations to perform
    returns: top 4 lines 

    '''
    inlier_dict = {}
    count = 0
    # repeat over the number of iterations to perform
    while count < numit:
        # select 2 random points
        rand1 = random.randint(0, len(features)-1)
        rand2 = random.randint(0, len(features)-1)
        sample1 = features[rand1]
        sample2 = features[rand2]
        inliers = 0
        # count the number of inliers on the line between the points
        for pt in features:
            if pt not in [sample1, sample2]:
                if (isinlier(sample1, sample2, pt)):
                    features.remove(pt)
                    inliers += 1
        inlier_dict[(sample1, sample2)] = inliers
        count += 1
    # get the top 4 lines with the most inliers
    inliers_sorted = dict(sorted(inlier_dict.items(), key = operator.itemgetter(1), reverse = True)[:4])
    return inliers_sorted

######################################
## Get m and b for line definition. ##
######################################

def get_parameters(p1, p2):
    '''
    Parameters: p1, p2 - two distinct points
    returns: the parameters for the equation of the line between the points

    '''
    x1 = p1[0]
    y1 = p1[1]
    x2 = p2[0]
    y2 = p2[1]
    if (x2 != x1):
        m  = (y2 - y1)/(x2 - x1)
        b = int(y1 - (m * x1))
        return (m,b)
    return None

##################################
## Perform Hough Transformation ##
##################################

def hough(features, numit):
    '''
    Parameters: features - set of points to run hough transformation on
                numit - number of iterations to complete
    returns: returns the endpoints of the 4 lines it detects

    '''
    points = {}
    # repeat for number of iterations
    for count in range(numit):
        rand1 = random.randint(1, len(features)-1)
        rand2 = random.randint(1, len(features)-1)
        samp1 = features[rand1]
        samp2 = features[rand2]
        parameters = get_parameters(samp1, samp2)
        if parameters is None:
            continue
        if parameters not in points.keys():
            points[parameters] = 1
        else:
            points[parameters] += 1
    # sort the points to get the top 4 lines
    sorted_points = sorted(points.items(), key = operator.itemgetter(1), reverse = True)
    four = dict(sorted_points[:4])
    lines = []
    # for each line, store the endpoints 
    for pt in four:
        y_int = (0,pt[1])
        scndpt = (5000, pt[0]*5000+pt[1])
        endpoints = (y_int, scndpt)
        lines.append(endpoints)
    return lines

##############################
## Convert image to matrix. ##
##############################

def im2matrix(im):
    '''
    Parameters: im - an image 
    returns: matrix - the matrix that translates to the given image

    '''
    matrix = []
    for x in range(0, im.width):
        curr = []
        for y in range(0, im.height):
            intens = im.getpixel((x,y))
            curr.append(intens)
        matrix.append(curr)
        curr = []
    return matrix

##################################
## Apply given filter to image. ##
##################################

def filt(im_filter, im):
    '''
    Parameters: im_filter - the desired filter
                im - the image to run the filter on
    returns: matrix of the image after the filter is run

    '''
    matrix = im2matrix(im)
    h = im.height
    w = im.width
    newim = [[0] * w] # pad newim with 0s (top)
    for y in range(1, h - 1):
        curr = [0] # pad newim with 0s (left)
        for x in range(1, w - 1):
            # apply the filter at each pixel in the image
            gsum = sum([
                im_filter[0][0]*matrix[x-1][y-1],
                im_filter[0][1]*matrix[x][y-1],
                im_filter[0][2]*matrix[x+1][y-1],
                im_filter[1][0]*matrix[x-1][y],
                im_filter[1][1]*matrix[x][y],
                im_filter[1][2]*matrix[x+1][y],
                im_filter[2][0]*matrix[x-1][y+1],
                im_filter[2][1]*matrix[x][y+1],
                im_filter[2][2]*matrix[x+1][y+1]])
            intensity = int(gsum/9)
            curr.append(intensity)
        curr.append(0) # pad newim with 0s (right)
        newim.append(curr)
    newim.append([0]*w) # pad newim with 0s (bottom)
    return newim

################################################
## Get important points from an image matrix. ##
################################################

def get_features(matrix):
    '''
    Parameters: matrix - the matrix of the suppressed image 
    returns: features - the interesting points of the matrix

    '''
    features = []
    for x in range(len(matrix[0])):
        for y in range(len(matrix)):
            # if the pixel is "interesting" (not set to black)
            if matrix[y][x] != 0:
                features.append((x,y))
    return features

##############################
## Convert matrix to image. ##
##############################

def matrix2im(matrix):
    '''
    Parameters: matrix - transformed matrix that corresponds to an image
    returns: image of the transformed matrix

    '''
    sz = (len(matrix[0]), len(matrix))
    newim = Image.new("L", (sz))
    for x in range(len(matrix[0])-1):
        for y in range(len(matrix)):
            px = matrix[y][x]
            pt = (x,y)
            newim.putpixel(pt, px)
    return newim
            
def main():
    
    im = Image.open("road.png")

    #####################
    ## Gaussian Filter ##
    #####################
    sigma = 3
    gaussfilt = gauss_kernel(sigma)
    G = filt(gaussfilt, im)
    Gim = matrix2im(G)
    Gim.save("gaussian_road.png")

    ###################
    ## Sobel Filters ##
    ###################

    '''
    define the sobel filters
    '''
    sobel_x = [
        [1 * SOBEL_MAGNITUDE, 0, -1 * SOBEL_MAGNITUDE],
        [2 * SOBEL_MAGNITUDE, 0, -2 * SOBEL_MAGNITUDE],
        [1 * SOBEL_MAGNITUDE, 0, -1 * SOBEL_MAGNITUDE]]
    sobel_y = [
        [1 * SOBEL_MAGNITUDE, 2 * SOBEL_MAGNITUDE, 1 * SOBEL_MAGNITUDE],
        [0, 0, 0],
        [-1 * SOBEL_MAGNITUDE, -2 * SOBEL_MAGNITUDE, -1 * SOBEL_MAGNITUDE]]


    
    sobelx = filt(sobel_x, Gim) # x direction
    sobelx_im = matrix2im(sobelx)
    sobely = filt(sobel_y, Gim) # y direction
    sobely_im = matrix2im(sobely)

    sobels = mysobel(sobely, sobelx)
    sobel_intensity = sobels[0]
    sobel_angels = sobels[1]
    thresh = hess_thresh(sobel_intensity, 140)
    sobel_im = matrix2im(thresh)
    sobel_im.save("sobel_road.png")

    #########################
    ## Hessian Suppression ##
    #########################
    
    hess_matrix = hess_suppress(sobels)
    hess_image = matrix2im(hess_matrix)
    im_copy = im.copy()
    draw = ImageDraw.Draw(im_copy)
    for x in range(len(hess_matrix[0])):
        for y in range(len(hess_matrix)):
            if hess_matrix[y][x] != 0:
                draw.point([x,y], "red")
    im_copy.save("hessian_road.png")
    
    features = get_features(hess_matrix)
    
    ############
    ## RANSAC ##
    ############
    
    im_copy = im.copy()
    draw = ImageDraw.Draw(im_copy)
    ransac_lines = ransac(features, 1000)
    for pt in ransac_lines.keys():
        draw.line([pt[0][0], pt[0][1], pt[1][0], pt[1][1]], "red", 1)
    im_copy.save("ransac_road.png")

    ##########################
    ## Hough Transformation ##
    ##########################
    lines = hough(features, 100000)
    im_copy = im.copy()
    draw = ImageDraw.Draw(im_copy)
    for pt in lines:
        draw.line([pt[0][0], pt[0][1], pt[1][0], pt[1][1]], "red", 1)
    im_copy.save("hough_road.png")

main()
        
    
    

    
    
