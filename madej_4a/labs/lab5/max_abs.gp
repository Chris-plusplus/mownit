#set style line 1 lt 1 lc rgb '#007F00' # red
#set style line 2 lt 1 lc rgb '#FFFF7F' # orange
#set style line 3 lt 1 lc rgb '#FF0000' # pale orange

# palette
set palette defined ( 0 '#00AF00',\
    	    	      1 '#FFFF7F',\
		      2 '#FF0000')


# Set plot parameters
set output 'max_abs_heatmap.png'
set xlabel "Liczba funkcji bazowych"
set ylabel "Liczba węzłów"
set title "Logarytm naturalny maksymalnego błędu"

set terminal png size 625,1250

set xrange[1:100]
set yrange[2:201]

set size ratio 2
set cbrange[1:10]

# Plot heatmap starting from X = N and Y = M
plot "__ls_max_abs_log.dat" with image title "Błąd"