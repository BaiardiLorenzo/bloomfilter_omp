import pandas as pd
import matplotlib.pyplot as plt


def plot():
    # Read the setup.csv file
    df = pd.read_csv('./results/csv/setup.csv', sep=';')

    tests = [2, 4, 6, 8, 10, 12, 14, 16]
    # Plot execution times
    plt.figure()
    plt.title('Setup: Execution times')
    plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Time (s)')
    plt.tight_layout()
    plt.legend()
    plt.savefig('./results/csv/setup_times.png')

    # Plot speedup
    plt.figure()
    plt.title('Setup: Speedup')
    plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Speedup')
    plt.legend()
    plt.tight_layout()
    plt.savefig('./results/csv/setup_speedup.png')

    # Read the filter.csv file
    df = pd.read_csv('./results/csv/filter.csv', sep=';')

    tests = [2, 4, 6, 8, 10, 12, 14, 16]
    # Plot execution times Filter1
    plt.figure()
    plt.title('Filter1: Execution times')
    plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['tPar{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Time (s)')
    plt.legend()
    plt.tight_layout()
    plt.savefig('./results/csv/filter1_times.png')

    # Plot speedup Filter1
    plt.figure()
    plt.title('Filter1: Speedup')
    plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['speedUp{}'.format(i)], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Speedup')
    plt.legend()
    plt.tight_layout()
    plt.savefig('./results/csv/filter1_speedup.png')

    plt.figure()
    plt.title('Filter2: Execution times')
    plt.plot(df['test'], df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['tPar{}'.format(i)+'Type2'], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Time (s)')
    plt.legend()
    plt.tight_layout()
    plt.savefig('./results/csv/filter2_times.png')

    plt.figure()
    plt.title('Filter2: Speedup')
    plt.plot(df['test'], df['tSeq']/df['tSeq'], '-o', label='Sequential')
    for i in tests:
        plt.plot(df['test'], df['speedUp{}'.format(i)+'Type2'], '-o', label='{} Threads'.format(i))
    plt.xlabel('Selected emails')
    plt.ylabel('Speedup')
    plt.legend()
    plt.tight_layout()
    plt.savefig('./results/csv/filter2_speedup.png')

    # plt.show()


if __name__ == '__main__':
    plot()
