#include "LoremIpsum.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

int Data(char *DataBuffer){//781bytes
	sprintf(DataBuffer,"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean vel turpis sit amet erat laoreet lacinia ut a risus. Nam sit amet est nec sapien volutpat vehicula. Fusce dignissim metus vel ipsum consectetur, ac tincidunt risus scelerisque. Integer sed justo nec turpis faucibus tincidunt sit amet ut dolor. Phasellus nec aliquam arcu, ac pharetra mauris. Donec ac sapien quis eros bibendum convallis. Etiam facilisis justo a lorem dapibus, nec commodo urna gravida. Integer non scelerisque turpis. Aenean dapibus sapien sed sapien elementum, non vulputate sapien dictum. Sed eget dui ultricies, luctus turpis a, egestas lorem. In in dui a est aliquam aliquam. Suspendisse potenti. Nullam vitae tincidunt justo. Integer pellentesque rutrum leo, eu vestibulum elit vulputate et.\r\n Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean vel turpis sit amet erat laoreet lacinia ut a risus. Nam sit amet est nec sapien volutpat vehicula. Fusce dignissim metus vel ipsum consectetur, ac tincidunt risus scelerisque. Integer sed justo nec turpis faucibus tincidunt sit amet ut dolor. Phasellus nec aliquam arcu, ac pharetra mauris. Donec ac sapien quis eros bibendum convallis. Etiam facilisis justo a lorem dapibus, nec commodo urna gravida. Integer non scelerisque turpis. Aenean dapibus sapien sed sapien elementum.\r\n");
//	char *temp=DataBuffer;
////	sprintf(temp,"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean vel turpis sit amet erat laoreet lacinia ut a risus. Nam sit amet est nec sapien volutpat vehicula. Fusce dignissim metus vel ipsum consectetur, ac tincidunt risus scelerisque. Integer sed justo nec turpis faucibus tincidunt sit amet ut dolor. Phasellus nec aliquam arcu, ac pharetra mauris. Donec ac sapien quis eros bibendum convallis. Etiam facilisis justo a lorem dapibus, nec commodo urna gravida. Integer non scelerisque turpis. Aenean dapibus sapien sed sapien elementum, non vulputate sapien dictum. Sed eget dui ultricies, luctus turpis a, egestas lorem. In in dui a est aliquam aliquam. Suspendisse potenti. Nullam vitae tincidunt justo. Integer pellentesque rutrum leo, eu vestibulum elit vulputate et.\r\n");
//    for (int i = 0; i < 2; ++i) {
//        strcat(DataBuffer, temp); // Append the original string
//    }
	return strlen(DataBuffer);
}

