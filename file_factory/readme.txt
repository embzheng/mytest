
ʹ��˵�����ù��߿�����������һЩ�ض����ַ��������������޸��ַ���Ϊ�ض���ֵ��

�������������������Ҫ������ļ�����Ӧλ����д ��file_factory�� �ַ�����Ȼ��ִ����������
              file_factory [src_file] [ins_file] [loop_num]
              src_file ΪԴ�ļ���ins_fileΪ�����ļ���loop_numΪ�������

�����޸Ĳ�����������������
              file_factory [src_file] [findstr] [ins_num] [grow]
              src_file ΪԴ�ļ���findstrΪ��Ҫ�޸ĵ��ַ�����ins_numΪ�޸�д��
              �����֣�ע��ins_num�����滻��findstr��ĩβ������findstrΪ��sctp-port=36418����
              ins_numΪ123�����滻���findstrΪ��sctp-port=36123�� ������ins_num���ֵĳ���
              ��С��findstr�ĳ��ȣ�����ᵼ���޸Ĵ���growΪins_numÿ�����ӵ���ֵ��

���ӣ�

Դ�ļ�Config_final.xml.4000gw  �����ļ�ins_180-si-dell-0721-Config_final.xml

[root@root file_factory]# ./file_factory Config_final.xml.4000gw ins_180-si-dell-0721-Config_final.xml 4000
src_file:Config_final.xml.4000gw ins_file:ins_180-si-dell-0721-Config_final.xml loop_num:4000
src_file len:6737
ins_file len:262
insert success!
[root@root file_factory]# ./file_factory Config_final.xml.4000gw henb-gw-index=\"1000 1000 1
src_file:Config_final.xml.4000gw findstr:henb-gw-index="1000 ins_num:1000 grow:1
src_file len:1054725
modification success!
[root@root file_factory]# ./file_factory Config_final.xml.4000gw henb-gw-id=\"1000 1000 1
src_file:Config_final.xml.4000gw findstr:henb-gw-id="1000 ins_num:1000 grow:1
src_file len:1054725
modification success!
[root@root file_factory]# ./file_factory Config_final.xml.4000gw sctp-port=\"36412 36412 1
src_file:Config_final.xml.4000gw findstr:sctp-port="36412 ins_num:36412 grow:1
src_file len:1054725
modification success!
[root@root file_factory]#