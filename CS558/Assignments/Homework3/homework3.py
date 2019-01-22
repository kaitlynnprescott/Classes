import math
import random
import operator
from PIL import Image, ImageDraw, ImageColor


###########################################
## Compute rgb distance between 2 points ##
###########################################

def rgb_dist(x, y):
    '''
    Parameters: x, y - two points
    returns: distance between the points
        x[0] -> R
        x[1] -> G
        x[2] -> B
    '''
    r = (x[0] - y[0])**2
    g = (x[1] - y[1])**2
    b = (x[2] - y[2])**2
    return math.sqrt(r + g + b)


#######################################
## Compute distance between 2 points ##
#######################################

def dist(x, y):
    '''
    Parameters: x, y - two points
    returns: distance between the points
        x[0] -> R
        x[1] -> G
        x[2] -> B
    '''
    return math.sqrt((x[0] - y[0])**2 + (x[1] - y[1])**2)


##############################
## Convert matrix to image. ##
##############################

def matrix2im(matrix):
    '''
    Parameters: matrix - transformed matrix that corresponds to an image
    returns: image of the transformed matrix

    '''
    sz = (len(matrix), len(matrix[0]))
    newim = Image.new("RGB", (sz))
    for x in range(len(matrix)-1):
        for y in range(len(matrix[0])):
            px = (matrix[x][y])
            pt = (x,y)
            newim.putpixel(pt, px)
    return newim


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


################################
## Apply kmeans segmentation. ##
################################

def kmeans_segmentation(k, im):
    '''
    Algorithm:
    1. Randomly guess k cluster center locations
    2. Each data point finds out what center it's closest to
    3. Each center finds the centroid of the points it owns
    4. Each center jumps to centroid
    5. Repeate 2-4 until center == centroid of points
    '''

    data = im2matrix(im)
    h = len(data) # num rows
    w = len(data[0]) # num cols
    # randomly guess k cluster centers
    centroids = []
    for i in range(k):
        x = random.randint(1, h-1)
        y = random.randint(1, w-1)
        pnt = data[x][y]
        centroids.append(pnt)
    
    # set initial centers to old_centroids to compare when to stop
    old_centroids = None

    # can there be an error function?
    
    while old_centroids != centroids:
        old_centroids = centroids
        # for each point in data, find the center it's closest to
        # and assign it to that cluster

        # list of lists of cluster values
        clusters = [[] for _ in range(k)]
        # list of lists of locations of all pixels in each cluster
        locations = [[] for _ in range(k)]
        for x in range(h):
            for y in range(w):
                dists = []
                rgb_datapnt = data[x][y]
                # rgb_datapnt is the rgb values of the pixel at position x,y
                for i in range(k):
                    rgb_center = old_centroids[i] 
                    # rgb_center is the rgb values of the pixel at center point i
                    dist_to_center = rgb_dist(rgb_center, rgb_datapnt)
                    dists.append(dist_to_center)
                min_ind, min_val = min(enumerate(dists), key=operator.itemgetter(1))
                clusters[min_ind].append(rgb_datapnt)
                locations[min_ind].append((x,y))
        
        # for each cluster
        for i in range(k):
            r = 0
            g = 0
            b = 0
            this_cluster = clusters[i]
            # for each point in cluster i
            for x in this_cluster:
                # add to sum of r
                r += x[0]
                # add to sum of g
                g += x[1]
                # add to sum of b
                b += x[2]
            # new center of clusters[i] is avg of each r, g, b
            r = r/len(this_cluster)
            g = g/len(this_cluster)
            b = b/len(this_cluster)
            centroids[i] = (r, g, b)
    
    # represent each clusters[i] as centroids[i]
    # for each cluster
    for i in range(k):
        # for each point in that cluster
        for xy in locations[i]:
            # get x and y values of location
            x = xy[0]
            y = xy[1]
            # set data[x][y] to the centroid of the cluster it's in
            data[x][y] = centroids[i]

    # now data is the segmented image
    return data


################################
## Compute Gradient Magnitute ##
################################

def grad_mag(grad):
    dx = grad[0]
    dy = grad[1]
    magnitude = math.sqrt((dx**2) + (dy**2))
    return magnitude


#############################################
## Compute Gradient Magnitude in RGB Space ##
#############################################

def rgb_grad(cent, low, right):
    # low is cent[x][y+1]
    # right is cent[x+1][y]
    r_mag = grad_mag((cent[0]-low[0], cent[0]-right[0]))
    g_mag = grad_mag((cent[1]-low[1], cent[1]-right[1]))
    b_mag = grad_mag((cent[2]-low[2], cent[2]-right[2]))
    combined_mag = math.sqrt((r_mag**2) + (b_mag**2) + (g_mag**2))
    return combined_mag


#############################
## Residual Error Function ##
#############################

def residual_error(old, new):
    sum = 0
    for k in range(len(old)):
        # add squares of distances
        old_center = old[k]
        new_center = new[k]
        pnt1 = (old_center[0], old_center[1])
        pnt2 = (new_center[0], new_center[1])
        sum += dist(pnt1, pnt2)**2
    # get square root of sum of squares
    return sum

########################
## SLIC Implementation##
########################

def slic(im, max_iter, threshold):
    '''
    Algorithm:
    1. Initialization: divide image in blocks of 50x50 pixels
        and initialize a centroid at the center of each block
    2. Local Shift: compute the magnitude of the gradient in each of
        the RGB color channels and use the square root of the sums of
        the 3 magnitudes as the combined gradient magnitude. Move the
        centroids to the position of the smallest gradient magnitude 
        in 3x3 windows centered on intial centroids
    3. Centroid Update: assign each pixel to its nearest centoid in the
        5D space (x,y,R,G,B) and recompute centroids. Use euclidean dist
        in the space, but divide x and y by 2.
    4. Optionally, only compare pixels to centroids within a distance of
        100 pixels (2x block size) during updates.
    5. IF (not converged) and (iterations < max_iter) 
        THEN go to step 2 (use max_iter = 3)
    6. Display output image as the SLIC slide: color pixels touching 2
        different clusters black, the remaining pixels the avg RGB value
        of their cluster.
    '''
    block_size = 50
    data = im2matrix(im)
    h = len(data) # num rows (y_max)
    w = len(data[0]) # num cols (x_max)
    print h
    print w 

    centroids = []
    gradients = []
    # initialize centroids
    for i in range(0,h-(block_size/2),block_size):
        for j in range(0,w-(block_size/2),block_size):
            # block is i + 49, j+49
            # centroid is (i+49)/2, (j+49)/2
            x = (i+block_size/2)
            y = (j+block_size/2)
            cent = data[x][y]
            r = cent[0]
            g = cent[1]
            b = cent[2]
            centroids.append((x, y, r, g, b))
    
    print("Centroids Initialized")
    # Local Shift:
    # Move centroids to lowest gradient position in 3x3 neighborhood
    for k in range(len(centroids)):
        cent = centroids[k]
        x = cent[0]
        y = cent[1]
        ilow = x - 1
        ihigh = x + 1
        jlow = y - 1
        jhigh = y + 1
        magnitudes = []
        mag_loc = []
        for i in range(ilow, ihigh):
            for j in range(jlow, jhigh):
                # cent is data[i][j]
                # low is data[i][j+1]
                # right is data[i+1][j]
                mag = rgb_grad(data[i][j], data[i][j+1], data[i+1][j])
                magnitudes.append(mag)
                mag_loc.append((i,j))
        
        # get new centroid from neighborhood of 3x3
        min_ind, min_val = min(enumerate(magnitudes), key = operator.itemgetter(1))
        min_grad = magnitudes[min_ind]
        center = mag_loc[min_ind]
        cent_x = center[0]
        cent_y = center[1]
        new_cent_val = data[cent_x][cent_y]
        centroids[k] = (cent_x, cent_y, new_cent_val[0], new_cent_val[1], new_cent_val[2]) 
    print("Centroids set by magnitudes")
    # Centroid Update:
    # Assign each pixel to nearest centroid in 100x100 (2*block_size) block
    error = float('inf')
    iterations = 0
    # set distance to infinity for each pixel
    d = [[float('inf') for _ in range(w)] for _ in range(h)]
    
    while (error >= threshold) or (max_iter > iterations):
        print "iteration: ", iterations
        iterations += 1
        clusters = [[] for _ in range(len(centroids))]
        locations = [[] for _ in range(len(centroids))]
        # for each centroid
        for k in range(len(centroids)):
            cent = centroids[k]
            x = cent[0]
            y = cent[1]
            # get block of 100 x 100
            if x <= 50:
                xmin = 0
            else:
                xmin = x - 50
            if y <= 50:
                ymin = 0
            else:
                ymin = y - 50
            
            if h >= w-50:
                xmax = h
            else:
                xmax = x+50
            if y >= w-50:
                ymax = w
            else:
                ymax = y+50

            # for each pixel in 100 x 100 block
            for i in range(xmin, xmax-1):
                for j in range(ymin, ymax-1):
                    # get distance from pixel to centroid
                    pnt1 = (x/2,y/2)
                    pnt2 = (i,j)
                    dist_to_centroid = dist(pnt1, pnt2)
                    if dist_to_centroid < d[i][j]:
                        d[i][j] = dist_to_centroid
                        pnt = data[i][j]
                        clusters[k].append((i, j, pnt[0], pnt[1], pnt[2]))
                        locations[k].append((i,j))
 
        # update centroids (to be mean x, y, r, g, b)
        old_centroids = centroids
        for k in range(len(centroids)):
            xsum = 0
            ysum = 0
            rsum = 0
            gsum = 0
            bsum = 0
            for pxl in clusters[k]:
                xsum += pxl[0]
                ysum += pxl[1]
                rsum += pxl[2]
                gsum += pxl[3]
                bsum += pxl[4]
            total = len(clusters[k])
            if total == 0:
                total = 1
            x = xsum/total
            y = ysum/total
            r = rsum/total
            g = gsum/total
            b = bsum/total
            centroids[k] = (x, y, r, g, b)

        # compute error
        error = residual_error(old_centroids, centroids)
    
    # pixels touching 2 clusters are black
    for k in range(len(centroids)):
        # for all pixels in cluster k
        for pxl in locations[k]:
            x = pxl[0]
            y = pxl[1]
            # if any neighboring pixel is not in the locations of cluster[k]
            # set that pixel to be black
            if (x-1, y-1) not in locations[k]:
                data[x][y] = 0
            elif (x-1, y) not in locations[k]:
                data[x][y] = 0
            elif (x-1, y+1) not in locations[k]:
                data[x][y] = 0
            elif (x, y-1) not in locations[k]:
                data[x][y] = 0
            elif (x, y+1) not in locations[k]:
                data[x][y] = 0
            elif (x+1, y-1) not in locations[k]:
                data[x][y] = 0
            elif (x+1, y) not in locations[k]:
                data[x][y] = 0
            elif (x+1, y+1) not in locations[k]:
                data[x][y] = 0
            else:
                avg = centroids[k]
                data[x][y] = (avg[2], avg[3], avg[4])
    print "Done"
    return data

####################
## Main function. ##
####################

def main():
    # k_means_im = Image.open('white-tower.png')
    # k = input("How many clusters?\n")
    # data = kmeans_segmentation(k, k_means_im)
    # kmeans_im = matrix2im(data)
    # kmeans_im.save("k_means_white_tower.png")
    
    slic_im = Image.open('wt_slic.png')
    data = slic(slic_im, 3, 1)
    slic_segmented = matrix2im(data)
    slic_segmented.save("slic_segmented_wt.png")
    
main()
