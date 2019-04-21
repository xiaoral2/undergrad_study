clc
clear

Fs = 48000; % Sampling Freq (Hz)
load('user3.mat')
plot(user3,'r--')
tt3=abs(user3)';
mal = ones(400,1);
Maverage3 = filter(mal,1,tt3);
t=(1:length(Maverage3))/Fs;
figure(1),plot(user3),hold on
low=4;
count=0;
m=0;
for i=1:length(Maverage3)
    if Maverage3(i)>4
        count=count+1;
    else
        if count>0.2*Fs
            isolate=user3(i-count:i);
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
% s=isolate;
% order=2
% r=zeros(order,1);
% R=zeros(order,order);
% for n=(order+1):length(s)
%     snj1=zeros(order,1);
%     for k=1:order
%         snj1(k)=s(n-k);
%     end
%     r=r+s(n)*snj1;
%     R=R+snj1*transpose(snj1);
% end
% coefficient=inv(R)*r

for m=1:1
    p=3;
    suum=0;
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
    r=sum(snew')'
    a=inv(R)*r
    %a{n}=inv(R)*r
%     b(n)=a{n}(1)
%     c(n)=a{n}(2)
    suum=suum+a;
end
mu=suum
suum=0;
for m=1:1
    n=1:length(segment{m});
    qwer=a-mu;
    suum=suum+qwer*qwer';
end
ck=suum
% for unw=1:length(mu)
%     unwdis=(a-mu)'*(a-mu)
% end
% 
% for mah=1:length(mu)
%     Mahdis=(a-mu)'*inv(ck)*(a-mu)
% end

a1=lpc(isolate,p)
est=filter([1 a1(2:end)],1,isolate);
e=isolate-est;
mean(e)