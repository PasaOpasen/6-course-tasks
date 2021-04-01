
xp = [0.68, 0.73, 0.80, 0.88, 0.93, 0.99];
yp = [0.80866, 0.89492, 2.02964, 1.20966, 1.34087, 1.52368];

xf = [0.68:0.005:0.99];

lin = interp1 (xp, yp, xf);
pch = interp1 (xp, yp, xf, "cubic");
spl = interp1 (xp, yp, xf, "spline");
plot (xf, lin,"r", xf,lin,"b", xf,pch,"p", xf,spl,"m",
      xp,yp,"r*");
legend ("original", "linear", "cubic", "spline");

# https://octave.org/doc/v4.0.0/One_002ddimensional-Interpolation.html