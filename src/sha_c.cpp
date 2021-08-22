#include "sha_c.hpp"

#define ERROR(comment) \
    printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment);

SHA_c::SHA_c()
{
}

SHA_c::~SHA_c()
{
}

using namespace std;

string SHA_c::sha1_cal(const string &src) const
{

    SHA_CTX sha_ctx;
    if (!(SHA1_Init(&sha_ctx)))
    {
        ERROR("SHA1_Init");
        return nullptr;
    }
    if (!(SHA1_Update(&sha_ctx, (void *)src.c_str(), src.length())))
    {
        ERROR("SHA1_Update");
        return nullptr;
    }

    string result;
    unsigned char *buf = static_cast<unsigned char *>(calloc(sizeof(unsigned char), SHA_DIGEST_LENGTH + 1));
    if (!(SHA1_Final(buf, &sha_ctx)))
    {
        ERROR("SHA1_Final");
        return nullptr;
    }

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        result.push_back(buf[i]);
    }
    return result;
}

string SHA_c::sha2_cal(const string &src, const SHA_c::SHA2_bit bit) const
{
    string result;
    if (bit == SHA_c::SHA2_bit::SHA_224)
    {
        SHA256_CTX ctx;
        unsigned char *buf = static_cast<unsigned char *>(calloc(sizeof(unsigned char), SHA224_DIGEST_LENGTH + 1));
        if (!SHA224_Init(&ctx))
        {
            ERROR("SHA224_Init");
            return nullptr;
        }

        if (!SHA224_Update(&ctx, src.c_str(), src.length()))
        {
            ERROR("SHA224_Update");
            return nullptr;
        }
        if (!SHA224_Final(buf, &ctx))
        {
            ERROR("SHA224_Final");
            return nullptr;
        }

        for (int i = 0; i < SHA224_DIGEST_LENGTH; i++)
        {
            result.push_back(buf[i]);
        }
        free(buf);
        buf = nullptr;
        return result;
    }
    if (bit == SHA_c::SHA2_bit::SHA_256)
    {
        SHA256_CTX ctx;
        unsigned char *buf = static_cast<unsigned char *>(calloc(sizeof(unsigned char), SHA256_DIGEST_LENGTH + 1));
        if (!SHA256_Init(&ctx))
        {
            ERROR("SHA256_Init");
            return nullptr;
        }
        if (!SHA256_Update(&ctx, src.c_str(), src.length()))
        {
            ERROR("SHA256_Update");
            return nullptr;
        }
        if (!SHA256_Final(buf, &ctx))
        {
            ERROR("SHA256_Final");
            return nullptr;
        }
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            result.push_back(buf[i]);
        }
        free(buf);
        buf = nullptr;
        return result;
    }
    if (bit == SHA_c::SHA2_bit::SHA_384)
    {
        SHA512_CTX ctx;
        unsigned char *buf = static_cast<unsigned char *>(calloc(sizeof(unsigned char), SHA384_DIGEST_LENGTH + 1));
        if (!SHA384_Init(&ctx))
        {
            ERROR("SHA384_Init");
            return nullptr;
        }
        if (!SHA384_Update(&ctx, src.c_str(), src.length()))
        {
            ERROR("SHA384_Update");
            return nullptr;
        }
        if (!SHA384_Final(buf, &ctx))
        {
            ERROR("SHA384_Final");
            return nullptr;
        }
        for (int i = 0; i < SHA384_DIGEST_LENGTH; i++)
        {
            result.push_back(buf[i]);
        }
        free(buf);
        buf = nullptr;
        return result;
    }
    if (bit == SHA_c::SHA2_bit::SHA_512)
    {
        SHA512_CTX ctx;
        unsigned char *buf = static_cast<unsigned char *>(calloc(sizeof(unsigned char), SHA512_DIGEST_LENGTH + 1));
        SHA512_Init(&ctx);
        SHA512_Update(&ctx, src.c_str(), src.length());
        SHA512_Final(buf, &ctx);
        if (!SHA512_Init(&ctx))
        {
            ERROR("SHA512_Init");
            return nullptr;
        }
        if (!SHA512_Update(&ctx, src.c_str(), src.length()))
        {
            ERROR("SHA512_Update");
            return nullptr;
        }
        if (!SHA512_Final(buf, &ctx))
        {
            ERROR("SHA512_Final");
            return nullptr;
        }

        for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        {
            result.push_back(buf[i]);
        }
        free(buf);
        buf = nullptr;
        return result;
    }

    return nullptr;
}

string SHA_c::str2hex(const string &src) const
{
    stringstream buf;
    char p[10];
    for (uint i = 0; i < src.size(); i++)
    {
        sprintf(p, "%02x", (unsigned char)src[i]);
        buf << p;
    }
    return buf.str();
}
