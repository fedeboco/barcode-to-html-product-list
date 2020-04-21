# Barcode number to HTML product from database interpreter

Reads a csv listing scanned barcodes, compares them with the system database and outputs a formatted product list with detailed info.

## Example Use

![](./usage_example.png)
<img src="https://github.com/fedeboco/barcode-to-html-product-list/blob/master/example/text4224-7-4.png?raw=true">

## Authors
* Federico Pérez Boco
* Patricio Richter

Project developed for "95.11 - Algoritmos y Programación I" for the Electronic Engineering Career in FIUBA.

## Use

Introduce the following command in a linux command line terminal:
```
./inventory -<fmt> -<itemsFileName.csv (relative path)> -<catalogFileName.csv (relative path)> -<outputFileName.outputFormat>
```
Where:

* ```<fmt>``` can be "xml" or "html"
* ```<itemsFileName.csv>``` is the csv file with a list of barcode numbers
* ```<outputFileName.outputFormat>``` is the output file in either HTML or XML format.

