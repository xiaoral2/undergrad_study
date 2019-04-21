clc
clear all;

Fs = 48000; % Sampling Freq (Hz)
load('user2.mat')
plot(user2,'r--')
tt2=abs(user2)';
mal = ones(400,1);
Maverage2 = filter(mal,1,tt2);
t=(1:length(Maverage2))/Fs;
figure(1),plot(user2),hold on
low=4;
count=0;
m=0;
for i=1:length(Maverage2)
    if Maverage2(i)>4
        count=count+1;
    else
        if count>0.2*Fs
            isolate=user2(i-count:i);
            figure(1),plot([(i-count) (i-count)],[-1 1], 'r--')
            figure(1),plot([i i],[-1 1], 'r--')
            s=i;
            m=m+1;
            segment{m}=isolate;
        end
        count=0;
    end
end 
t=(1:length(isolate))/Fs;
figure(2),plot(isolate),hold on;

%Question 2: Model Order Selection
% Choose an order P for the linear prediction

for m=1:1
    p=10;
    N=length(segment{m})
    s=segment{m};
    e=1;
    R=zeros(p,p);
    for n=(p+1):N
        snn=zeros(p,1);
        for k=1:p
            snn(k)=s(n-k);
        end
        snew(:,e)=s(n)*snn;
        sdsds =snn*snn';    
        R=R+snn*snn';
        e=e+1; 
    end
    r=sum(snew')';
    a=inv(R)*r;
%     mu=(1/p)*sum(a)
%     c=(1/p)*sum((a-mu)'*(a-mu))
end