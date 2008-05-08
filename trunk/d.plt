#set terminal jpeg small
set xrange [0:1000]
#set yrange [0:0.005]

plot "record" using 1:2

#    "record-r" using 1:2
#    "record-w" using 1:2, \
#    "record-r" using 1:2
#plot "record-jw" using 1:2, \
#    "record-jr" using 1:2, \
#    "record-jfw" using 1:2, \
#    "record-jfr" using 1:2
#    "record-w" using 1:2, \
#    "record-r" using 1:2, \
#    "record-fw" using 1:2, \
#    "record-fr" using 1:2
