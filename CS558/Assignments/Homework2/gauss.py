import math

def gauss_kernel(sigma):
    sz = 3
    kernel = np.zeros((sz, sz))
    ksum = 0
    for x in range(sz):
        xsq = x**2
        for y in range(sz):
            ysq = y**2
            twosigma = 2.0*(sigma**2)
            twopisigma = 1.0*(twosigma*math.pi)
            pwr = -1*(xsq+ysq)/twosigma
            kernel[x][y] = math.e*pwr*twopisgima
            ksum += kernel[x][y]
    mult = 10/ksum
    for x in range(sz):
        for y in range(sz):
            kernel[x][y] *= mult
    return kernel
