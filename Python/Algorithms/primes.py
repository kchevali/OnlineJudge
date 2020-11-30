from math import floor
from decimal import *
from time import time


# get primes the standard way (sieve)
# find the first ~500,000 primes in about 1sec
class Primes:

    def __init__(self, n):
        self.size = n + 1
        self.primes = []
        self.bs = [True] * self.size
        self.bs[0] = False
        self.bs[1] = False
        for i in range(2, self.size):
            if (self.bs[i]):
                for j in range(i * i, self.size, i):
                    self.bs[j] = False
                self.primes.append(i)

    def isPrime(self, N):
        if (N < self.size):
            return self.bs[N]
        for p in self.primes:
            if (N % p == 0):
                return False
        return True

# get initial constant


def getF(p):
    total = Decimal(0)
    mult = Decimal(1)
    for i in range(len(p.primes)):
        prime = p.primes[i]
        total += Decimal(prime - 1) / mult
        mult *= Decimal(prime)
        if i % 100 == 0:
            print("Getting F:", round(100.0 * i / len(p.primes), 4), end="%\r")
    print("Done!")

    return total

# get next constant: floored = primes


def next(f):
    return floor(f) * (f - floor(f) + 1)


# show time in minutes
def formatTime(t):
    return round(t / 60, 4)


if __name__ == '__main__':
    getcontext().prec = int(1e4)  # number of decimal digits

    startTime = time()
    p = Primes(int(1e7))  # get primes(standard way)

    primeTime = time()
    f = getF(p)  # get constant

    fTime = time()
    good = True
    for i in range(len(p.primes)):  # testing primes
        prime = int(floor(f))
        if prime != p.primes[i]:
            good = False  # failed
            print("Correct:", 100.0 * i / len(p.primes), "%")
            print(i, "primes found", len(p.primes), "total primes")
            break
        f = next(f)
    compTime = time()
    if good:
        print("PASS ALL")

    print("Gen Time:", formatTime(primeTime - startTime), "min")
    print("Get F:", formatTime(fTime - primeTime), "min")
    print("Compare Time", formatTime(compTime - fTime), "min")

    # record:20,448 primes found using the constant (~hour)
    # sieve record: 664,579 (~3 seconds)
