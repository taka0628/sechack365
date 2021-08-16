#include "RSA_c.hpp"
#include "dynamic_mem_c.hpp"

#define ERROR(comment) \
    printf("[ERROR]\n\t%s: %d\n\t%s\n", __func__, __LINE__, comment);

RSA_c::RSA_c()
{
    this->key_size = 0;
    this->pub_key = nullptr;
    this->priv_key = nullptr;
    this->key_pair = nullptr;
    this->PUB_FILE_NAME = "RSA_public_key";
    this->PRIV_FILE_NAME = "RSA_private_key";
}

RSA_c::~RSA_c()
{
    if (this->priv_key)
    {
        OPENSSL_free(this->priv_key);
        this->priv_key = nullptr;
    }
    if (this->pub_key)
    {
        OPENSSL_free(this->pub_key);
        this->pub_key = nullptr;
    }
    if (this->key_pair)
    {
        OPENSSL_free(this->key_pair);
        this->key_pair = nullptr;
    }
    this->key_size = 0;
}

using namespace std;

string RSA_c::decode_base64(string strData) const
{
    /*
        変換テーブル
    */
    const static unsigned char baTable[256] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0xff, 0xff, 0xff, 0x3f, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    string strRet;
    string::iterator ite = strData.begin();
    string::iterator iteEnd = strData.end();

    while (ite != iteEnd)
    {

        unsigned long dwValue = 0;
        int nBitCount = 0;

        // 4バイト単位で処理する
        int nCount = 4;
        while (nCount--)
        {

            // 1バイト取得
            dwValue <<= 6;
            if (ite != iteEnd)
            {
                unsigned char bChar = baTable[*ite++];
                if (64 > bChar)
                {
                    dwValue |= bChar;
                    nBitCount += 6;
                }
                else if (0xfe == bChar)
                {

                    // 改行コードは完全に無視する
                    nCount++;
                    dwValue >>= 6;
                }
            }
        }

        unsigned char *baTmp = (unsigned char *)&dwValue;

        // 並べ替え
        unsigned char baWrite[3] = {baTmp[2], baTmp[1], baTmp[0]};

        // 最大３バイトの書き込み
        int nByte = nBitCount / 8;
        if (0 < nByte)
        {
            strRet.append((char *)baWrite, nByte);
        }
    }

    // BASE64デコード結果を返す
    return (strRet);
}

string RSA_c::encrypt(const string &in) const
{
    dynamic_mem_c buf;
    buf.d_new(RSA_size(this->pub_key));

    int out_size = RSA_public_encrypt(in.size(), (unsigned char *)in.c_str(), buf.mem, this->pub_key, RSA_PKCS1_OAEP_PADDING);
    if (out_size <= 0)
    {
        int error = ERR_get_error();
        string str_error;
        str_error = ERR_reason_error_string(error);
        printf("%s\n", str_error.c_str());
        ERROR("RSA_public_encrypt");
        return nullptr;
    }

    string result;
    buf.copy(result, out_size);

    return result;
}

string RSA_c::decrypt(const string &in) const
{
    dynamic_mem_c buf;
    buf.d_new(this->key_size);
    int out_size = RSA_private_decrypt(in.length(), (unsigned char *)in.c_str(), buf.mem, this->priv_key, RSA_PKCS1_OAEP_PADDING);
    if (out_size <= 0)
    {
        int error = ERR_get_error();
        string str_error;
        str_error = ERR_reason_error_string(error);
        printf("%s\n", str_error.c_str());
        ERROR("RSA_private_decrypt");
        return nullptr;
    }

    string result;
    buf.copy(result, out_size);

    return result;
}

void RSA_c::create_key(const uint bit)
{
    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);

    this->key_pair = RSA_new();
    RSA_generate_key_ex(this->key_pair, (int)bit, bn, NULL);
    this->key_size = bit;

    this->create_RSA_file(KEY_STATUS::PRIV_KEY, this->PRIV_FILE_NAME);
    this->create_RSA_file(KEY_STATUS::PUB_KEY, this->PUB_FILE_NAME);

    BN_free(bn);
    bn = nullptr;
}

string RSA_c::str2hex(const string &str) const
{
    stringstream buf;
    char p[10];
    for (size_t i = 0; i < str.size(); i++)
    {
        sprintf(p, "%02x", (unsigned char)str[i]);
        buf << p;
    }
    return buf.str();
}

string RSA_c::hex2bin(const string &hex) const
{
    char buf[3] = {0};
    unsigned char *bin = (unsigned char *)calloc(sizeof(char), hex.size());
    int binsize = hex.size();
    printf("binsize: %d\n", binsize);

    string result;
    result.erase(result.begin(), result.end());
    char *pch;
    memset((void *)bin, 0, hex.size());
    for (size_t i = 0; i < hex.size(); i += 2)
    {
        buf[0] = hex[i];
        buf[1] = hex[i + 1];
        pch = buf;
        bin[i / 2] = (unsigned char)strtoul(pch, NULL, 16);
        // cout << "strtoil: " << strtoul(pch, NULL, 16) << endl;
        result.push_back(bin[i / 2]);
    }
    free(bin);
    bin = nullptr;
    return result;
}

string RSA_c::get_pub_key() const
{
}

void RSA_c::create_RSA_file(KEY_STATUS pem_type, std::string file_name)
{
    FILE *fp = nullptr;

    if (pem_type == KEY_STATUS::PUB_KEY)
    {
        fp = fopen(file_name.c_str(), "w");
        PEM_write_RSAPublicKey(fp, this->key_pair);
        fclose(fp);

        fp = fopen(file_name.c_str(), "rb");
        PEM_read_RSAPublicKey(fp, &this->pub_key, NULL, NULL);
        fclose(fp);
    }
    else if (pem_type == KEY_STATUS::PRIV_KEY)
    {
        fp = fopen(file_name.c_str(), "w");
        PEM_write_RSAPrivateKey(fp, this->key_pair, NULL, NULL, this->key_size, NULL, NULL);
        fclose(fp);

        fp = fopen(file_name.c_str(), "rb");
        PEM_read_RSAPrivateKey(fp, &this->priv_key, NULL, NULL);
        fclose(fp);
    }

    fp = nullptr;
}

string RSA_c::get_string_key(const KEY_STATUS &key) const
{
    string result;
    if (key == KEY_STATUS::PUB_KEY)
    {
        ifstream iss(this->PUB_FILE_NAME);
        if (!iss)
        {
            ERROR("!iss");
            return nullptr;
        }
        string buf;
        while (!iss.eof())
        {
            std::getline(iss, buf);
            result += buf + "\n";
        }
        result.erase(0, strlen("-----BEGIN RSA PUBLIC KEY-----") + 1);
        result.erase(result.find("-----END RSA PUBLIC KEY-----") - 1);
    }
    else if (key == KEY_STATUS::PRIV_KEY)
    {
        ifstream iss(this->PRIV_FILE_NAME);
        if (!iss)
        {
            ERROR("!iss");
            return nullptr;
        }
        string buf;
        while (!iss.eof())
        {
            std::getline(iss, buf);
            result += buf + "\n";
        }
        result.erase(0, strlen("-----BEGIN RSA PRIVATE KEY-----") + 1);
        result.erase(result.find("-----END RSA PRIVATE KEY-----") - 1);
    }

    string temp;

    return result;
}

void RSA_c::set_key()
{
    FILE *fp;
    fp = fopen(this->PUB_FILE_NAME.c_str(), "rb");
    PEM_read_RSAPublicKey(fp, &this->pub_key, NULL, NULL);
    fclose(fp);

    fp = fopen(this->PRIV_FILE_NAME.c_str(), "rb");
    PEM_read_RSAPrivateKey(fp, &this->priv_key, NULL, NULL);
    fclose(fp);
}
