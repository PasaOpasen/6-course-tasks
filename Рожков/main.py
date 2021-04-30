
import numpy as np


def euqlid(a,m):
    """
    av = d (mod m)

    returns d, v
    """
    s0 =0
    s1 = 1
    while True:
        q, r = m//a, m%a

        print(f"{m} = {a}*{q} + {r}")

        if r ==0:
            return a, s1
        s0, s1 = s1, -q*s1 + s0
        m, a = a, r


def one_eq(a,b,m):
    """
    au = b (mod m)
    """
    d, u0 = euqlid(a,m)

    u = int(b/d*u0)
    print(f"{a} u == {b} (mod {m}) --> u = {u} (mod {m})")

    return u



def several_eq(states):
    """
    states = [[a0,m0],[a1,m1],[a2,m2]]
    from x = a0 (mod m0) ...
    """
    arr = np.array(states)

    M = arr[:,1].prod()
    M_ = np.array([M/arr[i,1] for i in range(arr.shape[0])], dtype=np.int32)

    b = np.array([one_eq(M_[i], arr[i,0], arr[i, 1]) for i in range(arr.shape[0])])

    B = M_.dot(b)
    tmp = " + ".join([f"{m}*{bb}" for m, bb in zip(M_, b)])
    print(f'Total: x = {tmp} (mod {M}) = {B} (mod {M})')





     
# several_eq([
#     [3,5],
#     [5,7],
#     [7,9]
# ])


one_eq(7, 8, 123)

