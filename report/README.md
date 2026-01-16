# Building the Report

Ensure you have `latexmk` installed:

```bash
    sudo apt install latexmk
```

In the `report` directory:

```bash
    make
```

This will create the file `report.pdf`, containing the whole content, alongside necessary auxiliary files which are to be ignored.
If you want to clean up the `report` directory back to its state before compiling:

```bash
    make distclean
```
