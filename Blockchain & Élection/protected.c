#include "protected.h"

Protected* init_protected(Key* pKey, char* mess, Signature* sign) {
	Protected* pr = (Protected*) malloc(sizeof(Protected));
	pr->pKey = pKey;
	pr->mess = strdup(mess);
	pr->sign = sign;
	return pr;
}

int verify(Protected* pr) {
	char* mess = decrypt(pr->sign->content, pr->sign->size, pr->pKey->val, pr->pKey->n);
	int i = strcmp(pr->mess, mess);
	free(mess);
	return i;
}

void liberer_protected(Protected* pr) {
    free(pr->pKey);
    free(pr->mess);
    liberer_sign(pr->sign);
    free(pr);
}

char* protected_to_str(Protected* pr) {
	char* res;
	char buffer[256];
	sprintf(buffer, "%s %s %s\n", key_to_str(pr->pKey), pr->mess, signature_to_str(pr->sign));
	res = strdup(buffer);
	return res;
}

Protected* str_to_protected(char* str) {
	char pKey[256];
	char mess[256];
	char sign[256];
	sscanf(str, "%s %s %s\n", pKey, mess, sign);
	return init_protected(str_to_key(pKey), mess, str_to_signature(sign));
}

