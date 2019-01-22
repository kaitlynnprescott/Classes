import numpy as np
import math
import random
from PIL import Image, ImageDraw, ImageColor
from sklearn.neighbors import NearestNeighbors
from sklearn.neighbors import KNeighborsClassifier
from sklearn.cluster import KMeans

TARGET_COLORS = {"Red": (255, 0, 0), "Green": (0, 255, 0), "Blue": (0, 0, 255)}

##################################
## Get Difference of Two Colors ##
##################################

def color_difference (color1, color2):
    '''
    Parameters: color1 - RGB tuple of 1st color
                color2 - RGB tuple of 2nd color
    Returns: returns the sum of the difference of each component between 2 colors
    ex: c1: (165, 235, 78) c2: (185, 48, 204)
        abs(156-185) = 20, abs(235-48) = 187, abs(78-204) = 126
        20+187+126 = 333
    '''
    return sum([abs(component1-component2) for component1, component2 in zip(color1, color2)])


############################
## Get Likely Color Range ##
############################

def likely_color(color):
    '''
    Parameters: color - RBG tuple of a color
    Returns: name of color most likely to be base color
    '''
    differences = [[color_difference(color, target_value), target_name] for target_name, target_value in TARGET_COLORS.items()]
    differences.sort()  # sorted by the first element of inner lists
    my_color_name = differences[0][1]
    return my_color_name


#############################
## Length of List of Lists ##
#############################

def deep_len(lst):
    '''
    Parameters: list of elements
    Returns: the deep length of the list.
    '''
    return sum(deep_len(el) if isinstance(el, list) else 1 for el in lst)


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


#################################
## Separate RGB Color Channels ##
#################################

def getColorChannels(im):
    ''' 
    Parameters: im - image
    Returns: r, g, b - color channel matrices of im
    '''
    data = im.getdata()
    r = [(d[0],0,0) for d in data]
    g = [(0,d[1],0) for d in data]
    b = [(0,0,d[2]) for d in data]
    return [r, g, b]


##########################
## Image Representation ##
##########################

def im_rep(n, im):
    '''
    Parameters: im - image
                n - number of bins
    Returns: array of histogram values by bin 

    1. separate image into color channels
    2. get histogram of each color channel
    3. save as array [(R_bin1, G_bin1, B_bin1), ... (R_bin_n, G_bin_n, B_bin_n)]
    '''
    # separate image to color channels
    color_data = getColorChannels(im)
    r = color_data[0]
    g = color_data[1]
    b = color_data[2]

    # get histogram of each color channel
    r_hist = np.histogram(r, bins=n)
    g_hist = np.histogram(g, n)
    b_hist = np.histogram(b, n)

    # save as array of (R_bin_i, G_bin_i, B_bin_i)
    im_hist = []
    for i in range(n):
        im_hist.append([r_hist[0][i], g_hist[0][i], b_hist[0][i]])
    
    return im_hist


#######################
## Training Function ##
#######################

def im_training(n, im_array):
    '''
    Parameters: n - number of bins
                im_array - array of image arrays to run training on
    Returns: array of all histograms of images
    For each image in training set:
        get histogram of image
        store in array
    '''
    num_classes = len(im_array)
    # d = {}
    histograms = []
    # loop through classes
    for i in range(1, num_classes+1):
        # images in class i
        imgs = im_array[i-1]
        # loop through images
        for x in range(1,len(imgs)+1):
            # get hist output
            hist = im_rep(n, imgs[x-1])
            histograms.append(hist)
            # store in dictionary
            # ex: hist1class1 -> histogram of coast_train1
            #     hist2class2 -> histogram of forest_train2
            #d["hist{0}class{1}".format(x,i)] = hist
    # return dictionary
    histograms = np.array(histograms)
    nsamples, nx, ny = histograms.shape
    d2_histograms = histograms.reshape((nsamples, nx*ny))
    return histograms


######################
## Testing Function ##
######################

def im_testing(n, im_array, training):
    '''
    Parameters: n - number of bins
                im_array - array of images
                training - array of training image histograms
    Returns: accuracy of predictor
    For each image
        Get the histogram for that image.
        Get the closest image based on histogram.
        Get the class of the closest image, and assign the image to that class.
    Compute the accuracy of the predictor.
    '''
    num_classes = len(im_array)
    counter = 1
    correct = 0
    training = np.array(training)
    nsamples, nx, ny = training.shape
    #print nsamples, nx, ny
    d2_training = training.reshape((nsamples, nx*ny))
    #print d2_training
    for i in range(1, num_classes+1):
        # i is the class number of test images (i.e. (1)coast, (2)forest, (3)insidecity)
        imgs = im_array[i-1]
        num_imgs_in_class = len(imgs)
        for im in imgs:
            hist = im_rep(n, im)
            # use k-nearest neighbors to get closest image
            neigh = NearestNeighbors(n_neighbors=1)
            neigh.fit(d2_training)
            np_hist = np.array(hist)
            flat_hist = np_hist.ravel()
            flat_hist = [flat_hist]
            closest = neigh.kneighbors(flat_hist, return_distance=False)
            # compute predicted class -> should be 1, 2, or 3
            clss = ((closest+1) % num_classes) + 1
            print "Test image", "%02d" % (counter,), "of class", i, "has been assigned to class", clss[0][0]
            # accuracy check -> if correct, add to correct
            if int(clss[0][0]) == i: 
                correct = correct + 1
            counter += 1
    # accuracy
    total = float(deep_len(im_array))
    accuracy = correct / total
    return accuracy
    

##########################
## Pixel Classification ##
##########################

def pxl_class(sky, nonsky, k, test_imgs):
    '''
    Parameters: sky - image with sky
                nonsky - image without sky
                k - how many clusters
                test_img - image to 
    Returns:
    Saves image with sky turned to color red
    '''
    # iterate through images in test images and classify pixels
    for ind, im in enumerate(test_imgs,1):
        data = im2matrix(im)
        h = len(data) # num rows
        w = len(data[0]) # num cols
        # classify each pixel
        for x in range(h):
            for y in range(w):
                i = x-1
                if i < 0: i = 0
                j = y - 1
                if j < 0: j = 0

                k = x+1
                if k >= h: k = h-1
                l = y+1
                if l >= w: l = w-1

                rgb_data1 = np.array(data[i][j])
                rgb_data2 = np.array(data[i][y])
                rgb_data3 = np.array(data[i][l])
                rgb_data4 = np.array(data[x][j])
                rgb_data5 = np.array(data[x][y])
                rgb_data6 = np.array(data[x][l])
                rgb_data7 = np.array(data[k][j])
                rgb_data8 = np.array(data[k][y])
                rgb_data9 = np.array(data[k][l])
                if likely_color(rgb_data5) == "Blue":
                    # check surrounding
                    lc1 = likely_color(rgb_data1) == "Blue"
                    lc2 = likely_color(rgb_data2) == "Blue"
                    lc3 = likely_color(rgb_data3) == "Blue"
                    lc4 = likely_color(rgb_data4) == "Blue"
                    lc6 = likely_color(rgb_data6) == "Blue"
                    lc7 = likely_color(rgb_data7) == "Blue" 
                    lc8 = likely_color(rgb_data8) == "Blue" 
                    lc9 = likely_color(rgb_data9) == "Blue"
                    surr = lc1 + lc2 + lc3 + lc4 + lc6 + lc7 + lc8 + lc9
                    if surr >= 4:
                        # set to red
                        data[x][y] = (255, 0, 0)
        new_im = matrix2im(data)
        new_im.save("sky_test_output%s.png" % (ind))


###################
## Main Function ##
###################

def main():
    # convert all images to png (run once):
    # problem 1
    # coast1 = Image.open("ImClass/train/coast_train1.jpg")
    # coast1.save('coast_train1.png')
    # coast2 = Image.open("ImClass/train/coast_train2.jpg")
    # coast2.save('coast_train2.png')
    # coast3 = Image.open("ImClass/train/coast_train3.jpg")
    # coast3.save('coast_train3.png')
    # coast4 = Image.open("ImClass/train/coast_train4.jpg")
    # coast4.save('coast_train4.png')

    # forest1 = Image.open("ImClass/train/forest_train1.jpg")
    # forest1.save("forest_train1.png")
    # forest2 = Image.open("ImClass/train/forest_train2.jpg")
    # forest2.save("forest_train2.png")
    # forest3 = Image.open("ImClass/train/forest_train3.jpg")
    # forest3.save("forest_train3.png")
    # forest4 = Image.open("ImClass/train/forest_train4.jpg")
    # forest4.save("forest_train4.png")

    # city1 = Image.open("ImClass/train/insidecity_train1.jpg")
    # city1.save("insidecity_train1.png")
    # city2 = Image.open("ImClass/train/insidecity_train2.jpg")
    # city2.save("insidecity_train2.png")
    # city3 = Image.open("ImClass/train/insidecity_train3.jpg")
    # city3.save("insidecity_train3.png")
    # city4 = Image.open("ImClass/train/insidecity_train4.jpg")
    # city4.save("insidecity_train4.png")

    # test_coast1 = Image.open("ImClass/test/class1/coast_test1.jpg")
    # test_coast1.save("coast_test1.png")
    # test_coast2 = Image.open("ImClass/test/class1/coast_test2.jpg")
    # test_coast2.save("coast_test2.png")
    # test_coast3 = Image.open("ImClass/test/class1/coast_test3.jpg")
    # test_coast3.save("coast_test3.png")
    # test_coast4 = Image.open("ImClass/test/class1/coast_test4.jpg")
    # test_coast4.save("coast_test4.png")

    # test_forest1 = Image.open("ImClass/test/class2/forest_test1.jpg")
    # test_forest1.save("forest_test1.png")
    # test_forest2 = Image.open("ImClass/test/class2/forest_test2.jpg")
    # test_forest2.save("forest_test2.png")
    # test_forest3 = Image.open("ImClass/test/class2/forest_test3.jpg")
    # test_forest3.save("forest_test3.png")
    # test_forest4 = Image.open("ImClass/test/class2/forest_test4.jpg")
    # test_forest4.save("forest_test4.png")

    # test_city1 = Image.open("ImClass/test/class3/insidecity_test1.jpg")
    # test_city1.save("insidecity_test1.png")
    # test_city2 = Image.open("ImClass/test/class3/insidecity_test2.jpg")
    # test_city2.save("insidecity_test2.png")
    # test_city3 = Image.open("ImClass/test/class3/insidecity_test3.jpg")
    # test_city3.save("insidecity_test3.png")
    # test_city4 = Image.open("ImClass/test/class3/insidecity_test4.jpg")
    # test_city4.save("insidecity_test4.png")

    # problem 2
    # sky_train = Image.open("sky/sky_train.jpg")
    # sky_train.save("sky_train.png")
    # sky_mask = Image.open("sky/sky_train1.jpg")
    # sky_mask.save("sky_mask.png")
    # sky_test1 = Image.open("sky/sky_test1.jpg")
    # sky_test1.save("sky_test1.png")
    # sky_test2 = Image.open("sky/sky_test2.jpg")
    # sky_test2.save("sky_test2.png")
    # sky_test3 = Image.open("sky/sky_test3.jpg")
    # sky_test3.save("sky_test3.png")
    # sky_test4 = Image.open("sky/sky_test4.jpg")
    # sky_test4.save("sky_test4.png")

    # import all png images:
    # images for problem 1
    coast1 = Image.open("coast_train1.png")
    coast2 = Image.open("coast_train2.png")
    coast3 = Image.open("coast_train3.png")
    coast4 = Image.open("coast_train4.png")

    forest1 = Image.open("forest_train1.png")
    forest2 = Image.open("forest_train2.png")
    forest3 = Image.open("forest_train3.png")
    forest4 = Image.open("forest_train4.png")

    city1 = Image.open("insidecity_train1.png")
    city2 = Image.open("insidecity_train2.png")
    city3 = Image.open("insidecity_train3.png")
    city4 = Image.open("insidecity_train4.png")

    test_coast1 = Image.open("coast_test1.png")
    test_coast2 = Image.open("coast_test2.png")
    test_coast3 = Image.open("coast_test3.png")
    test_coast4 = Image.open("coast_test4.png")

    test_forest1 = Image.open("forest_test1.png")
    test_forest2 = Image.open("forest_test2.png")
    test_forest3 = Image.open("forest_test3.png")
    test_forest4 = Image.open("forest_test4.png")

    test_city1 = Image.open("insidecity_test1.png")
    test_city2 = Image.open("insidecity_test2.png")
    test_city3 = Image.open("insidecity_test3.png")
    test_city4 = Image.open("insidecity_test4.png")

    # images for problem 2
    sky_train = Image.open("sky_train.png")
    sky_mask = Image.open("sky_mask.png")
    sky_test1 = Image.open("sky_test1.png")
    sky_test2 = Image.open("sky_test2.png")
    sky_test3 = Image.open("sky_test3.png")
    sky_test4 = Image.open("sky_test4.png")

    # Problem 1:
    n = input("How many bins?\n")

    training_images = [[coast1, coast2, coast3, coast4], [forest1, forest2, forest3, forest4], [city1, city2, city3, city4]]
    # get training data set
    training_array = im_training(n, training_images)
    # make np array
    training_array = np.array(training_array)
    
    test_images = [ [test_coast1, test_coast2, test_coast3, test_coast4], [test_forest1, test_forest2, test_forest3, test_forest4], [test_city1, test_city2, test_city3, test_city4] ]
    
    # get testing results
    testing_results = im_testing(n, test_images, training_array)
    print testing_results


    # Problem 2:
    # import all png images for problem 2
    sky_train = Image.open("sky_train.png")
    sky_mask = Image.open("sky_mask.png")
    sky_test1 = Image.open("sky_test1.png")
    sky_test2 = Image.open("sky_test2.png")
    sky_test3 = Image.open("sky_test3.png")
    sky_test4 = Image.open("sky_test4.png")

    # 
    sky_test_set = [sky_test1, sky_test2, sky_test3, sky_test4]
    sky_pxl_class = pxl_class(sky_train, sky_mask, 10, sky_test_set)

main()

