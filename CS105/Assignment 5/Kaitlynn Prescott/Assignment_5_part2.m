close all
h0=input('Give the initial height of the ball: ');
v0=input('Give the initial velocity of the ball: ');
t=0:15;
ht=.5.*(-9.81).*t.^2+(v0).*t+h0;
vt=(-9.81).*t+v0;
figure(1);
hold on;
plot(t,ht,'c')
plot(t,vt,'r')
legend('height','velocity')
hold off;