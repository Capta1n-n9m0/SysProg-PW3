import subprocess as sp

REPO = "https://github.com/Capta1n-n9m0/SysProg-PW3"

def main():
    sp.run(["git", "clone", REPO])
    sp.run("cd SysProg-PW3;make", shell=True)

if __name__ == '__main__':
    main()