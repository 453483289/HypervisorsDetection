% ������� ���������� ������������ �� ������� ��������� ������ (T_i) �
% ��������������� ������������ ���� (var_ryad)
% ���� ������� ������������ ������������ 1, � ��������� ������ 0.

function [Is_present] = check_presence(Ti, FreqTable)

    Is_present = 0;
   
    len = length(FreqTable);
    for i=1:len
            if FreqTable(i) ==  Ti
               Is_present = 1;
               break;
            end
end

