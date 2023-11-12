#include "signature.h"

Signature* init_signature(long* content, int size) {
	Signature* sign = (Signature*) malloc(sizeof(Signature));
	sign->content = content;
	sign->size = size;
	return sign;
}

Signature* sign(char* mess, Key* sKey) {
	long* content = encrypt(mess, sKey->val, sKey->n);
	return init_signature(content, strlen(mess));
}

void liberer_sign(Signature* sign) {
    free(sign->content);
    free(sign);
}

char* signature_to_str(Signature* sign) {
	char* result = malloc(10*sign->size*sizeof(char));
	result[0] = '#';
	int pos = 1;
	char buffer[156];
	for(int i = 0; i < sign->size; i++) {
		sprintf(buffer, "%lx", sign->content[i]);	
		for(int j = 0; j < strlen(buffer); j++) {
			result[pos] = buffer[j];
			pos = pos + 1;
		}
		result[pos] = '#';
		pos = pos + 1;
	}
	result[pos] = '\0';
	result = realloc(result, (pos+1)*sizeof(char));
	return result;	
}

Signature* str_to_signature(char* str) {
	int len = strlen(str);
	long* content = (long*) malloc(sizeof(long)*len);
	int num = 0;
	char buffer[256];
	int pos = 0;
	for(int i = 0; i < len; i++) {
		if(str[i] != '#') {
			buffer[pos] = str[i];
			pos = pos + 1;
		} else {
			if(pos != 0) {
				buffer[pos] = '\0';
				sscanf(buffer, "%lx", &(content[num]));
				num = num + 1;
				pos = 0;
			}
		}
	}
	content = realloc(content, num*sizeof(long));
	return init_signature(content, num);	
}

