clc
clear

Fs = 48000; % Sampling Freq (Hz)
load('user1.mat')
load('user3.mat')
load('user2.mat')
plot(user1,'r--')

tt1=abs(user1)'; %absloute for user1,2,3
tt2=abs(user2)';
tt3=abs(user3)';

mal = ones(400,1);
Maverage1 = filter(mal,1,tt1);
Maverage2 = filter(mal,1,tt2);
Maverage3 = filter(mal,1,tt3);
t1=(1:length(Maverage1))/Fs;
% figure(1),plot(user1),hold on
low=4;
count=0;
m=0;
for i=1:length(Maverage1)
    if Maverage1(i)>4
        count=count+1;
    else
        if count>0.2*Fs
            isolate=user1(i-count:i);
            figure(1),plot([(i-count) (i-count)],[-1 1], 'r--')
            figure(1),plot([i i],[-1 1], 'r--')
            s=i;
            m=m+1;
            segment{m}=isolate;
        end
        count=0;
    end
end 
% t=(1:length(isolate))/Fs;
% figure(2),plot(isolate),hold on;
t2=(1:length(Maverage2))/Fs;
% figure(1),plot(user2),hold on
% low=4;
% count=0;
% m=0;
% for i=1:length(Maverage2)
%     if Maverage2(i)>4
%         count=count+1;
%     else
%         if count>0.2*Fs
%             isolate=user2(i-count:i);
%             figure(1),plot([(i-count) (i-count)],[-1 1], 'r--')
%             figure(1),plot([i i],[-1 1], 'r--')
%             s=i;
%             m=m+1;
%             segment{m}=isolate;
%         end
%         count=0;
%     end
% end 
% t=(1:length(isolate))/Fs;
% figure(3),plot(isolate),hold on;

t3=(1:length(Maverage2))/Fs;
%Question 2: Model Order Selection
% Choose an order P for the linear prediction

for m1=1:1
    p1=2;
    N1=length(segment{m})
    s1=segment{m};
    e1=1;
    R1=zeros(p1,p1);
    % snew=zeros(p,N-p-1);
    for n1=(p1+1):N1
        snn1=zeros(p1,1);
        for k1=1:p1
            snn1(k1)=s1(n1-k1);
        end
        snew1(:,e1)=s1(n1)*snn1;
        sdsds1 =snn1*snn1';    
        R1=R1+snn1*snn1';
        e1=e1+1; 
    end
    r1=sum(snew1')';
    a1=inv(R1)*r1;
end


%Question 4: Testing
%For utterance j in the test set of user m, calculate the LP coefficients a?jm and
%classify the origin of each utterance using
%  sum=0;
%     for n=1:length(trainword)
%         word=trainword{n};
%         lpcoe{n}=lpc(word,order);
%         sum=sum+lpcoe{n};        
%     end
%     mean{people}=sum/length(trainword);
% 
%     sum=0;
%     for n=1:length(trainword)
%         a=lpcoe{n}-mean{people};
%         sum=sum+a*a';
%     end
%     covariance{people}=sum/length(trainword);%15    
% end
