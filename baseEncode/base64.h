#ifndef   BASE64_H__
#define BASE64_H__ 1

#include <string>

// ����
std::string base64_encode(char const* bytes_to_encode, unsigned int in_len);
// ����
std::string base64_decode(std::string const& encoded_string);



#endif  // BASE64_H__