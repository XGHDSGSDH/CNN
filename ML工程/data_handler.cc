#include "data_handler.hpp"
#include<algorithm>
#include<stdint.h>
data_handler::data_handler()
{
	//指向空地方 
	data_array=new std::vector<data*>;
	training_data=new std::vector<data*>;
	test_data=new std::vector<data*>;
	validation_data=new std::vector<data*>;
}
data_handler::~data_handler()
{
	//啥也不用 
}

void data_handler::read_feature_vector(std::string path)
{
	uint32_t header[4];
	uint8_t bytes[4];
	FILE *f=fopen(path.c_str(),"rb");
	if(f)
	{
		for(int i=0;i<4;i++)
		{
			if(fread(bytes,sizeof(bytes),1,f))
			{
				header[i]=convert_to_little_endian(bytes);
			}
			else
			{
				printf("Error getting input file header.\n");
				exit(1);
			}
		}
		printf("Done getting file header.\n");
		int image_size=header[2]*header[3];
		//回data.hpp和.cc里面加上一个构造函数 
		for(unsigned int i=0;i<header[1];i++)
		{
			data* d=new data();
			uint8_t element[1];
			for(int j=0;j<image_size;j++)
			{
				if(fread(element,sizeof(element),1,f))
				{
					d->append_to_feature_vector(element[0]);
				}
				else
				{
					printf("Error reading from file.\n");
					exit(1);
				}
			}
			data_array->push_back(d);
		} 
		printf("Successfully read and stored %zu feature vectors.\n", data_array->size());
	}
	else
	{
		printf("Could not find file.\n");
		exit(1);
	}
	fclose(f);
}
void data_handler::read_feature_label(std::string path)
{
	uint32_t header[2];
	uint8_t bytes[4];
	FILE *f=fopen(path.c_str(),"r");
	if(f)
	{
		for(int i=0;i<2;i++)
		{
			if(fread(bytes,sizeof(bytes),1,f))
			{
				header[i]=convert_to_little_endian(bytes);
			}
			else
			{
				printf("Error getting input label file header.\n");
				exit(1);
			}
		}
		printf("Done getting label file header.\n");
		for(unsigned int i=0;i<header[1];i++)
		{
			uint8_t element[1];
			if(fread(element,sizeof(element),1,f))
			{
				data_array->at(i)->set_label(element[0]);
			}
			else
			{
				printf("Error reading from file.\n");
				exit(1);
			}
		}
		printf("Successfully read and stored %zu labels.\n",data_array->size());
	}
	else
	{
		printf("Could not find file.\n");
		exit(1);
	}
	fclose(f);
}
void data_handler::split_data()
{
	random_shuffle(data_array->begin(), data_array->end());
	//（回去看变量名 
	int training_end=data_array->size()*training_percent;
	int validation_end=training_end+data_array->size()*validation_percent;
	int test_end=data_array->size();
	
	for(int i=0;i<training_end;i++)
	{
		training_data->push_back(data_array->at(i));
	}
	for(int i=training_end;i<validation_end;i++)
	{
		validation_data->push_back(data_array->at(i));
	}
	for(int i=validation_end;i<test_end;i++)
	{
		test_data->push_back(data_array->at(i));
	}
	
	printf("Done splited data.\n");
	printf("Training data size: %zu.\n",training_data->size());
	printf("Test data size: %zu.\n",test_data->size());
	printf("Validation data size: %zu.\n",validation_data->size());
}
void data_handler::count_classes()
{
	int count=-1;
	for(unsigned int i=0;i<data_array->size();i++)
	{
		if(class_map.find(data_array->at(i)->get_label())==class_map.end())
		{
			class_map[data_array->at(i)->get_label()]=++count;
			data_array->at(i)->set_enumerated_label(count);
		}
		else
		{
			data_array->at(i)->set_enumerated_label(class_map[data_array->at(i)->get_label()]);
		}
	}
	num_classes=count+1;
	printf("Successfully extracted %d unique classes.\n",num_classes);
}

uint32_t data_handler::convert_to_little_endian(const uint8_t * bytes)
{
	return (uint32_t)((bytes[0]<<24)|(bytes[1]<<16)|(bytes[2]<<8)|(bytes[3]));
}

std::vector<data *> * data_handler::get_training_data()
{
	return training_data;
}
std::vector<data *> * data_handler::get_validation_data()
{
	return validation_data;
}
std::vector<data *> * data_handler::get_test_data()
{
	return test_data;
}
