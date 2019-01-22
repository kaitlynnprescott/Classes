import numpy as np
import math
import os
from PIL import Image, ImageDraw, ImageColor

#############################
## Verify histogram helper ##
#############################

def verify_hist(hist, n):
    '''
    Parameters: hist - histogram to verify
                n - expected number of bins
    Returns: True or False

    '''
    count = 0
    for i in hist:
        count = count + i
    if (count/3 == n):
        ## divide by 3 for 3 color channels
        return True
    else:
        return False


#################################
## Euclidean Distance Function ##
#################################

def euclidean_dist(x, y):
    '''
    Parameters: x - first point
                y - second point
    Results: distance between 2 points
    
    '''
    dist = 0.0
    for i in range(len(x)):
        dist = dist + ((x[i] - y[i])**2)
    return math.sqrt(dist)


###############################
## Create Histogram of Image ##
###############################

def createHist(file_path, h_bin):
    '''
    Parameters: file_path - path to image files
                h_bin - number of bins for the histogram
    Returns: histogram of new image
    
    '''
    test_files = len(os.listdir(file_path))
    hist = [[j, [0 for i in range(h_bin*3)]] for j in range(test_files)]
    index = 0
    for file in os.listdir(file_path):
        im = Image.open(file_path + file)
        im_arr = np.asarray(im)
        r, c, x = im_arr.shape
        for i in range(r):
            for j in range(c):
                hist[index][1][int((im_arr[i][j][0])/(256/h_bin))] = hist[index][1][int((im_arr[i][j][0])/(256/h_bin))] + 1
                hist[index][1][int((im_arr[i][j][1])/(256/h_bin)) + h_bin] = hist[index][1][int((im_arr[i][j][1])/(256/h_bin)) + h_bin] + 1
                hist[index][1][int((im_arr[i][j][2])/(256/h_bin)) + (h_bin*2)] = hist[index][1][int((im_arr[i][j][2])/(256/h_bin)) + (h_bin*2)] + 1

        if (verify_hist(hist[index][1], r*c)):
            print "Histogram of " + file + " is correct."
        else:
            print "Histogram of " + file + " is not correct."

        index = index + 1

    print()
    return hist


##########################
## Get Cluster Function ##
##########################

def get_clusters(hist, t_dist, kern):
    '''
    Parameters: hist - histogram to base clusters on
                t_dist - distance threshold
                kern - filter
    Returns: clusters and means of histogram
    
    '''
    means = []
    clusters = []
    for i in hist:
        x = i[1]
        conv = 0
        while(conv == 0):
            neigh = []
            conv = 1
            for im in hist:
                if (euclidean_dist(x, im[1]) < t_dist):
                    neigh.append(im)
            if (neigh != []):
                mean = meanshift(neigh, x, kern)
            if (mean != x):
                x = mean
                conv = 0
            else:
                if (mean not in means):
                    means.append(mean)
                    clusters.append([i[0]])
                else:
                    ind = means.index(mean)
                    clusters[ind].append(i[0])
    return clusters, means


##########################
## Mean Shift Algorithm ##
##########################

def meanshift(neigh, x, kern):
    '''
    Parameters: neigh - neighbors of x
                x 
                kern - filter
    Returns:
    '''
    size = len(neigh[0][1])
    mean = [0 for i in range(size)]
    for i in range(size):
        num = float(0)
        den = float(0)
        shift = float(0)
        for n in neigh:
            dist = euclidean_dist(n[1], x)
            weight = gauss(dist, kern)
            num = num + (weight * n[1][i])
            den = den + weight
        shift = num/den
        mean[i] = round(shift)
    return mean


#####################
## Gaussian Kernel ##
#####################
def gauss(dist, kern):
    val = (1/(kern*math.sqrt(2*math.pi))) * np.exp(-0.5*((dist/kern))**2)
    return val


############################
## Draw clusters to Image ##
############################
def drw(file_path, clusters, name):
    '''
    Parameters: file_path - path to images
                clusters
                name - name to save image under
    Returns: saves new images
    '''
    cluster_num = 1
    for clust in clusters:
        num_elem = len(clust)
        f = os.listdir(file_path)
        imr, imc, x = np.asarray(Image.open(file_path + f[0])).shape
        scale = math.ceil(math.sqrt(num_elem))
        r = imr * scale
        c = imc * scale
        new_im = Image.new('RGB', (int(c), int(r)), 1)
        new_im = np.asarray(new_im)
        new_im.setflags(write=1)
        i_init = 0
        j_init = 0
        scale_factor = 0
        for i in clust:
            im = np.asarray(Image.open(file_path + f[i]))
            rr, cc, xx = im.shape
            for i in range(rr):
                for j in range(cc):
                    new_im[i_init + i][j_init + j] = im[i][j]
            j_init = j_init + imc
            scale_factor = scale_factor + 1
            if (scale_factor == scale):
                i_init = i_init + imr
                j_init = 0
                scale_factor = 0
        new_im = Image.fromarray(new_im)
        new_im.save(name + '_cluster_' + str(cluster_num) + '.png')
        cluster_num = cluster_num + 1


###################
## Main Function ##
###################

def main():
    images1_path = "./imgs_1/"
    images2_path = "./imgs_2/"
    h_bin = 4
    hist1 = createHist(images1_path, h_bin)
    hist2 = createHist(images2_path, h_bin)
    t_dist = 50000.0
    kern = 30000.0
    clusters1, means1 = get_clusters(hist1, t_dist, kern)
    save1 = 'imgs1'
    drw(images1_path, clusters1, save1)
    clusters2, means2 = get_clusters(hist2, t_dist, kern)
    save2 = 'imgs2'
    drw(images2_path, clusters2, save2)
    

main()
