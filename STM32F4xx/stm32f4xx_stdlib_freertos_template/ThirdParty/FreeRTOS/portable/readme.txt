每个实时内核端口由三个包含核心内核的文件组成
组件并且对于每个端口是通用的，并且是一个或多个文件
特定于特定的微控制器和/或编译器。


+ FreeRTOS / Source / Portable / MemMang目录包含五个示例
内存分配器，如http://www.FreeRTOS.org网站上所述。

+其他目录每个都包含特定于特定的文件
微控制器或编译器，其中的目录名称
目录包含的特定文件。



例如，如果您对[architecture]的[compiler]端口感兴趣
微控制器，然后包含端口特定文件
FreeRTOS / Source / Portable / [compiler] / [architecture]目录。 如果这是
只有您感兴趣的端口，然后所有其他目录都可以
忽略。
