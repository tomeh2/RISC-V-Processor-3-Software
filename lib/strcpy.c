char* strcpy(char* dst, const char* src)
{
	char* temp = dst;
	while (*src)
		*dst++ = *src++;
	return temp;
}
