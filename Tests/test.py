#
# Paste the data you wish to graph in tab-delimited rows in the format:
#
#       xdata <tab> ydata
#
# In this example the xdata is time (s) and y data is y position (cm)
#

import math
import matplotlib.pyplot as plt

graham = [95.4794,94.0762,95.2992,94.3202,95.8312,94.3434,94.3516,93.9838,94.0366,96.2106]
monotone = [57.4508,61.7482,58.2604,55.3962,55.961,59.0982,59.0594,57.8548,61.5308,69.2606]
dnq = [198.901,188.642,183.337,183.323,184.064,188.846,192.779,200.639,227.569,276.604]
jarvis = [1794.36,3316.6,6395.3,13743.5,39121.2]
chan = [386.38,356.099,374.88,371.721,342.794,362.751,361.667,429.474,426.145,420.913]
kirk = [5265.16,10794.9,23521.4]

def f(a):
  return a
  # return [math.log2(_) for _ in a]

tlist = list(range(10, 20))
ylist = graham

#print "tlist=",tlist
#print "ylist=",ylist

plt.title('time (ms) vs. log(number of points on the hull)')
plt.xlabel('log(h)')
plt.ylabel('time (ms)')

plt.plot(tlist, f(graham), '--', label='GS')
plt.plot(tlist, f(monotone), '--', label='MCA')
plt.plot(tlist, f(dnq), '--', label='DAC')
# plt.plot(tlist[ : len(jarvis)], f(jarvis), '--', label='JS')
plt.plot(tlist, f(chan), '--', label='CA')
# plt.plot(tlist[ : len(kirk)], f(kirk), '--', label='KSA')

plt.ylim([0,600])
plt.legend()
plt.show()

