clear all;
close all;
plik=fopen("pliczek.txt",'r');
formatSpec = '%f';
A = fscanf(plik,formatSpec);
count=size(A);
for i=1:count
 B(i)=i+1;
end
B=B.';
plot(B,A);
