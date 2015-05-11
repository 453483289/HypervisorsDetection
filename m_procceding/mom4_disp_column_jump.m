% ������ �������� ��������������� � ��������� �� ���������� ������� �
% ������ ���������� �� ���.���� � �������� 
% ������� ���� �� 24 ��� 2011
%

% ������ �������������:
%
% 1) ������� ��������:
% TV3(:,3) - ������� �������� ������� ������, ���������� �� Excel
% 0.02 - ��������� �������� ������ ������������
% 1000 - ��������� �������� ������ ������� (������)
% 
% 2) ����� �������:
% mean_disp_column_jump(TR3(:,1), 0.02, 1000);
% 
% 3) ������������ ������ - ��������� � ������ 4-��� ������� ��� �������
% 
% � ���������� ������ ������� � ������� ������ Matlab ����� 
% �������� ������������ ������� �������������� � ���������

function [res] = mom4_disp_column_jump(T_column_in, threshold_frequence_in, threshold_jump_in)

% 1) ������� ������� T_column ��������� ����� Excel
T_column = T_column_in;

% 3) ���������� ������� � ������ ��������� ������ ���������� 
% threshold_in = 0.05;
threshold_frequence = threshold_frequence_in;
T_column_filtr = column_filtr(T_column, threshold_frequence);
threshold_jump = threshold_jump_in;
mom4_column = 0;    
disp_column = 0;
 
if length(T_column_filtr) > 1    
    % 4) ���������� ������������ �� ������ � ��� ������� ������� ������������
    % ����������
   
    diff_line = diff(T_column_filtr);
       
  
   fprintf('%i \n', max(abs(diff_line)) )
   
        
    i_start = 1;   
    
%     plot (T_column_filtr, '.r');
%     hold on 
%     plot (diff_line, 'o');

%      ������ ���������
%     fprintf('\n/``````````````\\\n');
    i=2;
    num_jumps = 0;
    while (i<length(diff_line))   
         if ( threshold_jump < abs( diff_line(i) ) ) 
%              && ( abs( diff_line(i) ) < 4000) 
             i_finish = i-1;
             one_line = T_column_filtr(i_start:i_finish); % ���������� ������� � ������(**�������) � �� �������
             koef = (i_finish-i_start)/length(diff_line); % ������� ����������
             mom4_column = mom4_column + ( sum((one_line - mean(one_line)).^4)./length(one_line) ) * koef; % ����������� ������ 4-�� �������                      
             disp_column = disp_column + ( std(one_line, 1)^2 ) * koef; 
             i = i + 2;
             i_start = i;
             num_jumps = num_jumps + 1;
%            fprintf('\n������ ������ � %i\n', i );
         end;
         i = i + 1;
    end;
%     fprintf('\n\\____________/\n');
    
%     fprintf('%i ', num_jumps );

    i_finish = length(diff_line) + 1;
    one_line = T_column_filtr(i_start:i_finish); % ���������� ������� � ������(**�������) � �� �������
    koef = (i_finish-i_start)/length(diff_line); % ������� ����������
    mom4_column = mom4_column + ( sum((one_line - mean(one_line)).^4)./length(one_line) ) * koef; % ����������� ������ 4-�� �������                  
    disp_column = disp_column + ( std(one_line, 1)^2 ) * koef; 
%     fprintf('\n������� �����. �� �����������=%0.2f\n������� �������� ������=%f\n', threshold_frequence_in, threshold_jump_in );
%     fprintf('������� �����.=%0.2f\n���������=%0.2f\n', res(1), res(2));
else
%     fprintf('\n������� �����.=%f\n ������ �� �������\n', threshold);
end

res = [disp_column, mom4_column];