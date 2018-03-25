# Cairo_Graph
Scripts for graphs in C++ using Cairo graphics Library (www.cairographics.org)

# Build
```sh
sudo apt-get install libcairo2-dev
cd Cairo_Graph
g++ cairo_line_graph.cpp -o cairo_line_graph $(pkg-config --cflags --libs cairo)
```
# Running the Program
```sh
./cairo_line_graph
```
Input all the co-ordinates as per the prompt
Output is saved in graph.png
