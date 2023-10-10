import pandas as pd
from matplotlib import pyplot as plt

results_filename = 'results.csv'
plot_filename = 'plot.png'


def plot_csv_data(csv_filename):
    data = pd.read_csv(csv_filename, delimiter=';')

    test_key = 'test'
    time_seq_key = 'tSeq'
    time_par_keys = [f'tPar{i}' for i in range(2, len(data.columns) - 2, 2)]
    speedup_keys = [f'speedUp{i}' for i in range(2, len(data.columns) - 2, 2)]
    fpr_key = 'fpr'

    plt.figure(figsize=(24, 8))

    # Plot times
    plt.subplot(1, 3, 1)
    plt.plot(data[test_key], data[time_seq_key], marker='o', label='Sequential')
    for i, time_par_key in enumerate(time_par_keys):
        plt.plot(data[test_key], data[time_par_key], marker='o', label=f'Parallel {i*2 + 2} Threads')
    plt.xlabel('Test Sizes')
    plt.ylabel('Time (seconds)')
    plt.title('Time vs. Test Sizes')
    plt.legend()

    # Plot speedup
    plt.subplot(1, 3, 2)
    for i, speedup_key in enumerate(speedup_keys):
        plt.plot(data[test_key], data[speedup_key], marker='o', label=f'Parallel {i*2 + 2} Threads')
    plt.xlabel('Test Sizes')
    plt.ylabel('Speedup')
    plt.title('Speedup vs. Test Sizes')
    plt.legend()

    # Plot false positive rate
    plt.subplot(1, 3, 3)
    plt.plot(data[test_key], data[fpr_key], marker='o', label='False Positive Rate')
    plt.xlabel('Test Sizes')
    plt.ylabel('False Positive Rate')
    plt.title('FPR vs. Test Sizes')
    plt.legend()

    plt.tight_layout()
    plt.savefig(plot_filename)
    plt.show()


"""def plot_results(results):
    print(results)
    plt.figure(figsize=(24, 8))

    # Plot times
    plt.subplot(1, 3, 1)
    plt.plot(results[test_key], results[time_seq_key], marker='o', label='Sequential')
    for i in test_threads:
        plt.plot(results[test_key], results[time_par_key+str(i)], marker='o', label=f'Parallel {i} Threads')
    plt.xlabel('Test Sizes')
    plt.ylabel('Time (seconds)')
    plt.title('Time vs. Test Sizes)')
    plt.legend()

    # Plot speedup
    plt.subplot(1, 3, 2)
    for i in test_threads:
        plt.plot(results[test_key], results[speedup_key+str(i)], marker='o', label=f'Parallel {i} Threads')
    plt.xlabel('Test Sizes')
    plt.ylabel('Speedup')
    plt.title('Speedup vs. Test Sizes')
    plt.legend()

    # Plot false positive rate
    plt.subplot(1, 3, 3)
    plt.plot(results[test_key], results[fpr_key], marker='o', label='False Positive Rate')
    plt.xlabel('Test Sizes')
    plt.ylabel('False Positive Rate')
    plt.title('FPR vs. Test Sizes')
    plt.legend()
    
    plt.tight_layout()
    plt.savefig(plot_filename)
    plt.show()
"""


def main():
    plot_csv_data(results_filename)


if __name__ == '__main__':
    main()
