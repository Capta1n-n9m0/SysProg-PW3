import subprocess as sp
import sys

REPO = "https://github.com/Capta1n-n9m0/SysProg-PW3"


def main(argv):
    sp.run(["git", "clone", REPO])
    if "exec" in argv:
        sp.run("cd SysProg-PW3;make", shell=True)


if __name__ == '__main__':
    main(sys.argv)

