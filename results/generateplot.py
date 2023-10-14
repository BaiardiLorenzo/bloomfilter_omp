import pandas as pd
from matplotlib import pyplot as plt

setup_results = 'csv/setup.csv'
filter_results = 'csv/filter.csv'

plot_setup_filename = 'plot/setup.png'
plot_filter_filename = 'plot/filter.png'


def plot_csv_data(csv_filename, plot_filename):
    data = pd.read_csv(csv_filename, delimiter=';')

    test_key = 'test'
    time_seq_key = 'tSeq'
    time_par_keys = [f'tPar{i}' for i in range(2, len(data.columns) - 2, 2)]
    speedup_keys = [f'speedUp{i}' for i in range(2, len(data.columns) - 2, 2)]
    fpr_key = 'fpr'

    fig, (times, speedups, fprs) = plt.subplots(1, 3, figsize=(24, 8))

    # Plot times
    times.plot(data[test_key], data[time_seq_key], marker='o', label='Sequential')
    for i, time_par_key in enumerate(time_par_keys):
        times.plot(data[test_key], data[time_par_key], marker='o', label=f'Parallel {i*2 + 2} Threads')
    times.set_xlabel('Test Sizes')
    times.set_ylabel('Time (seconds)')
    times.set_title('Time vs. Test Sizes')
    times.legend()

    # Plot speedup
    for i, speedup_key in enumerate(speedup_keys):
        speedups.plot(data[test_key], data[speedup_key], marker='o', label=f'Parallel {i*2 + 2} Threads')
    speedups.set_xlabel('Test Sizes')
    speedups.set_ylabel('Speedup')
    speedups.set_title('Speedup vs. Test Sizes')
    speedups.legend()

    # Plot false positive rate
    fprs.plot(data[test_key], data[fpr_key], marker='o', label='False Positive Rate')
    fprs.set_xlabel('Test Sizes')
    fprs.set_ylabel('False Positive Rate')
    fprs.set_title('FPR vs. Test Sizes')
    fprs.legend()

    # Save plot
    plt.tight_layout()
    plt.savefig(plot_filename)
    plt.show()


def main():
    plot_csv_data(setup_results, plot_filename=plot_setup_filename)
    plot_csv_data(filter_results,  plot_filename=plot_filter_filename)


if __name__ == '__main__':
    main()
