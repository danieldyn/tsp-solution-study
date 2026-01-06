PROJECT=report
LATEX=latexmk -pdf -use-make

all: $(PROJECT).pdf

$(PROJECT).pdf: $(PROJECT).tex sections/*.tex
	$(LATEX) $<

clean:
	$(LATEX) -c
	rm -f sections/*.aux

distclean:
	$(LATEX) -C
	rm -f $(PROJECT).pdf

.PHONY: all clean distclean
