from typing import Dict, List
import matplotlib.pyplot as plt
import matplotlib
import numpy as np


def uniform_units(arr: List) -> List:
    arr[0] *= 10**-3
    arr[1] *= 10**-3
    arr[2] *= 10**-3
    return arr

def plot(datadict: Dict, mode: str, fmt1: str, fmt2: str, ax: plt.Axes = None) -> None:
    is_new = False
    if ax is None:
        fig, ax = plt.subplots()
        is_new = True
    
    x = [10**x for x in datadict.keys()]
    my = [datadict[xx][0] for xx in datadict.keys()]
    qy = [datadict[xx][1] for xx in datadict.keys()]

    my = uniform_units(my)
    qy = uniform_units(qy)

    ax.plot(x, my, fmt1, label=f'Merge Sort {mode}')
    ax.plot(x, qy, fmt2, label=f'Quick Sort {mode}')

    # for i in range(len(datadict)):
    #     ax.text(x[i], my[i] + 10, f'({i}, {my[i]:.4f})')
    #     ax.text(x[i], qy[i] + 30, f'({i}, {qy[i]:.4f})')

    ax.set_title(mode)
    
    ax.set_xlabel('input size')
    ax.set_xscale('log')
    ax.set_xticks(x)

    ax.set_ylabel('time')
    # ax.set_yscale('log')

    ax.grid(True)
    ax.legend()

    if is_new:
        plt.show(block=False)
    



if __name__ == '__main__':
    datadict_asc = {
        1: (0.38454, 0.08683), 
        2: (3.6286, 2.0881), 
        3: (35.243, 45.749), 
        4: (0.36759, 0.84635), 
        5: (3.1243, 24.228), 
        6: (32.8754, 758.546)
    }

    datadict_desc = {
        1: (0.35568, 0.0844), 
        2: (3.7317, 5.0601), 
        3: (32.201, 549.866), 
        4: (0.8086, 52.9605), 
        5: (4.7529, 5278.78), 
        6: (50.032, 567573)
    }

    datadict_rand = {
        1: (0.30698, 0.16752), 
        2: (3.0576, 1.5977), 
        3: (66.135, 39.389), 
        4: (0.8976, 0.5984), 
        5: (8.6263, 5.2858), 
        6: (100.363, 50.2976)
    }

    fig, ax = plt.subplots()
    plot(datadict_asc, 'Ascending', '^-r', '^-m', ax)
    plot(datadict_desc, 'Descending', 'v-b', 'v-c', ax)
    plot(datadict_rand, 'Random', 'o-g', 'o-y', ax)
    plt.show(block=False)

    plot(datadict_asc, 'Ascending', '^-r', '^-m')
    plot(datadict_desc, 'Descending', 'v-b', 'v-c')
    plot(datadict_rand, 'Random', 'o-g', 'o-y')

    input()
