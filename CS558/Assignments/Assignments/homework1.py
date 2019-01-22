import math
import PIL as pillow
from PIL import Image


def myfilter(filt, im, sigma, threshold):
    if filt == 'gaussian':
        # window size
        sz = 6*sigma-1
        # compute kernel 
        kernel = np.zeros((sz, sz))
        max_len = int(sz/2)
        twosigma = 2.0*(sigma**2)
        twopisigma = 1.0/(twosigma*np.pi)

        for x in range(-max_len, max_len+1):
            xsq = x**2
            for y in range(-max_len, max_len+1):
                ysq = y**2
                pwr = -1*(xsq + ysq)/twosigma
                kernel[x+max_len][y+max_len] = np.exp(pwr) * twopisigma

        k_sum = np.sum(kernel)
        # normalize filter to be 1
        if k_sum != 1:
            kernel = np.divide(kernel, k_sum)

        # apply filter to image
        xmax = im.shape[0]
        ymax = im.shape[1]
        convolve = im.copy()

        for x in range(0, xmax):
            for y in range(0, ymax):
                convolve[x][y] = convolve_point(x, y, im, kernel)
        return convolve
    
    elif filt == 'sobel-x':
        sobel_x = np.array([
            [-1, 0, 1],
            [-2, 0, 2],
            [-1, 0, 1] ])

        # apply filter to image
        xmax = im.shape[0]
        ymax = im.shape[1]
        convolve = im.copy()

        for x in range(0, xmax):
            for y in range(0, ymax):
                convolve[x][y] = convolve_point(x, y, im, sobel_x)

        for i in range(0, xmax):
            for j in range(0, ymax):
                if convolve[i][j] == threshold:
                    convolve[i][j] = 0

        return convolve
    
    elif filt == 'sobel-y':
        sobel_y = np.array([
            [-1,-2,-1],
            [ 0, 0, 0],
            [ 1, 2, 1] ])

        # apply filter to image
        xmax = im.shape[0]
        ymax = im.shape[1]
        convolve = im.copy()

        for x in range(0, xmax):
            for y in range(0, ymax):
                convolve[x][y] = convolve_point(x, y, im, sobel_y)

        for i in range(0, xmax):
            for j in range(0, ymax):
                if convolve[i][j] == threshold:
                    convolve[i][j] = 0
                    
        return convolve
        
def gauss_kern(sigma):
    kernel = [[0,0,0],[0,0,0],[0,0,0]]
    ksum = 0
    for x in range(3):
        for y in range(3):
            xsq = x**2
            ysq = y**2
            twosigma = 2.0*(sigma**2)
            twopisigma = 1.0/(twosigma*math.pi)
            pwr = -1*(xsq + ysq)/twosigma
            kernel[x][y] = math.e*pwr * twopisigma
            ksum += kernel[x][y]
    mult = 10/ksum
    for x in range(3):
        for y in range(3):
            kernel[x][y] *= mult
    print(kernel)
    return kernel


def convolve_point(x, y, im, kernel):
    xmax = im.shape[0]
    ymax = im.shape[1]
    kxmax = kernel.shape[0]
    kymax = kernel.shape[1]
    kxmax = int(kxmax/2)
    kymax = int(kymax/2)
    conv_sum = np.int64(0)

    for kx in range(-kxmax, kxmax+1):
        for ky in range(-kymax, kymax+1):
            adjx = kx+x
            adjy = ky+y

            if adjx < 0:
                adjx = 0
            elif adjx >= xmax:
                adjx = xmax-1

            if adjy < 0:
                adjy = 0
            elif adjy >= ymax:
                adjy = ymax-1

            isum = kernel[kx+kxmax][ky+kymax] * im[adjx][adjy]
            conv_sum += isum
    return conv_sum

def non_max_suppression(im, threshold):
    xmax = im.shape[0]
    ymax = im.shape[1]

    suppress = im.copy()
    for x in range(0,xmax):
        for y in range(0, ymax):
            grad = gradient(x, y, im)
            gmag = np.sqrt(grad[0]**2 + grad[1]**2)
            if gmag < threshold:
                suppress[x][y] = 0

    for x in range(0, xmax):
        for y in range(0, ymax):
            non_max_suppress_point(x, y, suppress, suppress.copy())

    return suppressed

def non_max_suppress_point(x, y, im, original):
    if im[x][y] == 0:
        return
    xmax = im.shape[0]
    ymax = im.shape[1]
    grad = gradient(x, y, original)
    if grad[0] == 0:
        grad_dir = 1
    grad_dir = np.arctan(grad[1]/grad[0])
    deg = np.degrees(grad_dir)

    if abs(deg) > 90:
        deg = -1 * np.sign(deg) * (180 - abs(deg))
        
    if abs(deg) > 85:
        if y+1 >= ymax:
            yt = ymax-1
        yt = y+1
        
        if y == 0:
            yb = 0
        yb = y-1

        if original[x][y] < original[x][yt] or original[x][y] < original[x][yb]:
            im[x][y] = 0
    elif abs(deg) > 5:
        if original[x][y] < max_direc(x, y, deg, original):
            im[x][y] = 0
    else:
        if x+1 >= ymax:
            xr = xmax-1
        xr = x+1
        
        if x == 0:
            xl = 0
        xl = x-1

        if original[x][y] < original[xr][y] or original[x][y] < original[xl][y]:
            im[x][y] = 0


def max_direc(x, y, deg, im):
    xmax = im.shape[0]
    ymax = im.shape[1]
    if abs(deg) > 67.5:
        if y+1 >= ymax:
            yt = ymax-1
        yt = y+1
        if y==0:
            yb = 0
        yb = y-1
        max1 = im[x][yt]
        max2 = im[x][yb]
    elif abs(deg) > 22.5:
        if deg<0:
            if x+1 >= xmax:
                xn1 = xmax - 1
            xn1 = x+1
            if y == 0:
                yn1 = 0
            yn1 = y-1
            if x == 0:
                xn2 = 0
            xn2 = x-1
            if y+1 >= ymax:
                yn2 = ymax-1
            yn2 = y+1
        else:
            if x+1 >= xmax:
                xn2 = xmax - 1
            xn2 = x+1
            if y == 0:
                yn1 = 0
            yn1 = y-1
            if x == 0:
                xn1 = 0
            xn1 = x-1
            if y+1 >= ymax:
                yn2 = ymax-1
            yn2 = y+1
        max1 = im[xn1][yn1]
        max2 = im[xn2][yn2]
    else:
        if x+1 >= xmax:
            xr = xmax-1
        xr = x+1
        if x == 0:
            xl = 0
        xl = x-1

        max1 = im[xr][y]
        max2 = im[xl][y]

    return max(max1, max2)
    

def gradient(x, y, im):
    dfx = myfilter('sobel_x', im, 2, threshold)
    dfy = myfilter('sobel_y', im, 2, threshold)
    return np.array([dfx, dfy])


#################################
# Gaussian Filtering of images. #
#################################

R = mpimg.imread('red.png', 0)
R_gauss2 = myfilter('gaussian', R, 2, 0)

R_gauss5 = myfilter('gaussian', R, 5, 0)


########################################
# Compute Gradients with Sobel Filter. #
########################################

R_sobel_x = myfilter('sobel-x', R, 0, 250)
R_sobel_y = myfilter('sobel-y', R, 0, 250)


####################################
# Perform Non-Maximum Suppression. #
####################################

R_nonmax = non_max_suppression(R, 100)
R_plot = plt.imshow(R_nonmax)
plt.show()
