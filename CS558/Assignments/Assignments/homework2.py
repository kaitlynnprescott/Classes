import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

import homework1

def hessian(im, threshold, sigma, sz):
    '''
    Apply Gaussian Filter first
    Use Sobel filters as derivative operators
    Threshold the determinant of the Hessian
    Apply non-maximum suppression in 3 x 3 neighborhoods / vicinity
    '''
    G = homework1.myfilter('gaussian', im, 2, 100)
    Gx = homework1.myfilter('sobel-x', G, 2, 100)
    Gy = homework1.myfilter('sobel-y', G, 2, 100)
    Gxx = homework1.myfilter('sobel-x', Gx, 2, 100)
    Gxy = homework1.myfilter('sobel-y', Gx, 2, 100)
    Gyy = homework1.myfilter('sobel-y', Gy, 2, 100)

    determinants = Gxx * Gyy - (Gxy**2)
    xmax = determinants.shape[0]
    ymax = determinants.shape[1]
    for x in range(0, xmax):
        for y in range(0, ymax):
            if determinants[x][y] < threshold:
                determinants[x][y] = 0

    hess_suppress(im, determinants, sz)
    for x in range(0, xmax):
        for y in range(0, ymax):
            if determinants[x][y] >= localmax(x, y, determinants, sz) and determinants[x][y] != 0:
                im[x][y] = 1
            else:
                im[x][y] = 0
    
    features = []
    for x in range(0, xmax):
        for y in range(0, ymax):
            if im[x][y] == 1:
                features.append((x,y))

    return im, features


def localmax(x, y, im, sz):
    im_x = im.shape[0]
    im_y = im.shape[1]
    
    sz_len = int(sz/2)

    min_x = x - sz_len
    if min_x < 0:
        min_x = 0
    max_x = x + sz_len + 1
    if max_x >= im_x:
        max_x = im_x - 1
    min_y = y - sz_len
    if min_y < 0:
        min_y = 0
    max_y = y + sz_len + 1
    if max_y >= im_y:
        max_y = im_y - 1

    max_val = im[x][y]
    for i in range(min_x + 1, max_x):
        for j in range(min_y + 1, max_y):
            max_val = max(im[i][j], max_val)

def ransac(im, s, num_best, min_in, feature_thresh, sigma):
    '''
    Choose a small subset of points uniformly at random
    Fit a model to that subset
    Find all remaining points that are 'close' to the model
    If there are more than a certain number of inliers
      Refit using all the new inliers
    Reject the rest as outliers
    Repeat and choose the best model
    '''
    n = int(np.log(.01)/np.log(1 - (.25 ** s)))
    inlier_thresh = np.sqrt(3.84 * sigma**2)

    feat_im, features = hessian(im.copy(), feature_thresh, sigma)
    best_lines = []
    best_subs = []

    for br in range(num_best):
        subs = []
        lines = []
        error = []

        for rn in range(n):
            sub = None
            while sub is None or sub in subs or sub in best_subs:
                sub = subsamp(features, s)
            subs.appent(sub)

            dist_to, _ = fitline(sub)
            inliers = find_ins(dist_to, inlier_thresh, features)

            if len(inliers) >= min_in:
                lines.append(inliers)
                _, coefficients = fitline_many(inliers)
                error.appened(total_err(coefficients, inliers))


        if len(lines) > 0:
            min_err = error.index(min(error))
            best_lines.append(lines[min_err])
            best_subs.append(subs[min_err])
    plot_inlier(best_lines, im)
    return im

def plot_inlier(lines, im, maxPlot, sz):
    for ind in range(maxPlot):
        for pt in lines[ind]:
            plot_square(pt, sz, im)
            
        start = extreme_pts(lines[ind])[0]
        end = extreme_pts(lines[ind])[1]
        if start is not None and end is not None:
            plot_ln(start, end, im)

def plot_ln(st_pt, end_pt, im):
    rr, cc, val = line_aa(st_pt[0], st_pt[1], end_pt[0], end_pt[1])
    im[rr, cc] = 1

def plot_square(pt, sz, im):
    bounds = neighborhood_im_bound(pt[0], pt[1], sz, im)
    xs = bounds[0]
    ys = bounds[1]
    for x in range(xs[0], xs[1]):
        for y in range(ys[0], ys[1]):
            im[x][y] = 1

def subsamp(samp, sz):
    sub = []
    for s in range(sz):
        elem = None
        while elem is None or elem in sub:
            elem = sample[int(len(sample)*np.random.random())]
        sub.append(elem)
    return sub


def extreme_pts(ln):
    max_dist = 0
    st_pt = None
    end_pt = None
    for pt1 in ln:
        for pt2 in ln:
            dist = np.sqrt(((point2[0] - point1[0]) ** 2) + ((point2[1] - point1[1]) ** 2))
            if dist > max_dist:
                st_pt = pt1
                end_pt = pt2
                max_dist = dist
    return st_pt, end_pt
            

def total_err(coefficients, pts):
    err = 0
    a, b, c = coefficients
    for pt in pts:
        err += (a*pt[0] + b*pt[1] + c)**2
    return err


def find_ins(dist_to_model_fnc, thresh, features):
    inliers = []
    for pt in features:
        if dist_to_model_fnc(pt) < thresh:
            inliers.append(pt)
    return inliers


def fitline(pts):
    pt1 = pts[0]
    pt2 = pts[1]

    a = p1[1] - p2[1]
    b = p1[0] - p2[0]
    c = (p1[0] * p2[1]) - (p2[0] * p1[1])

    def dist_to(pt):
        return dist_func(a,b,c,pt)

    coefficients = a,b,c
    return dist_to, coefficients


def fitline_many(pts):
    xs = np.matrix([[x,1] for (x, _) in pts])
    ys = np.matrix([[y] for (_, y) in pts])
    try:
        bs = np.linalg.inv(xs.transpose() * xs) * xs.transpose() * ys
    except np.linalg.linalg.LinAlgError:
        return fitline(pts)

    m, b_intercept = bs[0].item(), bs[1].item()

    a = -m
    b = 1
    c = -b_intercept

    def dist_to(pt):
        return dist_funct(a, b, c, pt)

    coefficients = a, b, c
    return dist_to, coefficients


def dist_func(a, b, c, pt):
    top = np.abs(a*pt[0] + b*pt[1] + c)
    bottom = np.sqrt(a**2 + b**2)
    return top/bottom


def neighborhood_bounds(x, y, xmax, ymax, sz):
    sz_len = int(sz/2)

    min_x= x - sz_len
    if min_x < 0:
        min_x = 0

    max_x = x + sz_len + 1
    if max_x >= xmax:
        max_x = xmax - 1

    min_y = y - sz_len
    if min_y < 0:
        min_y = 0

    max_y = y + sz_len + 1
    if max_y >= ymax:
        max_y = ymax - 1

    return (min_x, max_x), (min_y, max_y)
    
def neighborhood_im_bound(x, y, sz, im):
    xmax = im.shape[0]
    ymax = im.shape[1]
    return neighborhood_bounds(x, y, xmax, ymax, sz)

def hough(im, feature_thresh, sigma):
    '''
    Discretize parameter space into bins (accumulator)
    For each feature point in the image
      Put a vote in every bin that could have generated this point
    Find bins that have the most votes
    Parameter space will be represented using a polar format
    '''

    xmax = im.shape[0]
    ymax = im.shape[1]
    theta = 180
    count = np.ndarray(shape=(theta, xmax+ymax))
    pts = np.ndarray(shape=(theta, xmax+ymax), dtype=object)
    for i in range(pts.shape[0]):
        for j in range(pts.shape[1]):
            pts[i][j] = []
    feat_im, features = hessian(im.copy(), feature_thresh, sigma)

    for pt in features:
        for t in range(theta):
            rho = int(pt[0]*np.cos(t) + pt[1]*np.sin(t))
            count[t][rho] += 1
            pts[t][rho].append(pt)

    maxes = local2dmax(counter, 3)
    plot_best(maxes, pts, im, 4, 3)
    return im


def local2dmax(counter, sz):
    maxes = []
    xmax = counter.shape[0]
    ymax = counter.shape[1]
    for x in range(xmax):
        for y in range(ymax):
            if counter[x][y] >= local_max(x,y,counter,sx):
                maxes.append((x,y))
    maxes.sort(key= lambda point: arr[point[0], point[1]], reverse = True)
    return maxes


def plot_best(maxes, pts, im, maxPlot, sz):
    for ind in range(maxPlot):
        line = pts[maxes[ind]]
        for pt in line:
            plot_square(pt, sz, im)

        points = extreme_pts(line)
        st = points[0]
        end = points[1]
        if st is not None and end is not None:
            plot_line(st, end, im)



###############################
# Hessian Filtering of image. #
###############################
R = mpimg.imread('/Users/katieprescott/Desktop/CS558/Assignments/Assignments/road.png')
R_hess = hessian(R, 2, 30, 3)

hess_plot = plt.imshow(R_hess)
