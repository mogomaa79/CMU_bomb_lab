import itertools
import subprocess

initial_lines = [
    "Border relations with Canada have never been better.",
    "1 2 4 8 16 32",
    "2 707",
    "7 0",
    "ionefg",
]

all_permutations = list(itertools.product([1, 2, 3, 4, 5, 6], repeat=6))

output_file = "br_ans.txt"

for index, permutation in enumerate(all_permutations, start=1):
    open(output_file, 'w').close()
    with open(output_file, "a") as file:
        for line in initial_lines:
            file.write(line + "\n")

        last_line = " ".join(map(str, permutation))
        file.write(last_line + "\n")

    bash_command = f"./bomb {output_file} >> out.txt"

    try:
        subprocess.run(bash_command, shell=True, check=True)
        print(f"File {output_file} executed successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error executing {output_file}: {e}")

    with open("out.txt", 'r') as f:
        if "BOOM" in f.read():
            open("out.txt", 'w').close()
        else:
            subprocess.run("cat br_ans.txt >> out.txt", shell=True, check=True)
            print(f.read())
            break