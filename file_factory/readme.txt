
使用说明：该工具可以批量插入一些特定的字符串，并可批量修改字符串为特定数值。

批量插入操作：先在需要插入的文件的相应位置填写 “file_factory” 字符串，然后执行以下命令
              file_factory [src_file] [ins_file] [loop_num]
              src_file 为源文件，ins_file为插入文件，loop_num为插入个数

批量修改操作：敲入以下命令
              file_factory [src_file] [findstr] [ins_num] [grow]
              src_file 为源文件，findstr为需要修改的字符串，ins_num为修改写入
              的数字，注意ins_num总是替换到findstr的末尾，比如findstr为“sctp-port=36418”，
              ins_num为123，则替换后的findstr为“sctp-port=36123” ，所以ins_num数字的长度
              需小于findstr的长度，否则会导致修改错误。grow为ins_num每次增加的数值。

例子：

源文件Config_final.xml.4000gw  插入文件ins_180-si-dell-0721-Config_final.xml

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