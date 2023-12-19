unsigned char encryptedOutputMessage[16];
unsigned char decryptedOutputMessage[16];

void encrypt16(char * plainText, char * key, unsigned char * outputBuffer)
{
  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb( &aes, MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void decrypt16(unsigned char * chipherText, char * key, unsigned char * outputBuffer)
{
  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, (const unsigned char*)chipherText, outputBuffer);
  mbedtls_aes_free( &aes );
}

void cleanEncryptedOutputMessage()
{
  for (int i = 0; i < 16; i++)
  {
    encryptedOutputMessage[i] = NULL;
  }
}

void cleanDecryptedOutputMessage()
{
  for (int i = 0; i < 16; i++)
  {
    decryptedOutputMessage[i] = NULL;
  }
}

void displayEncryptedOutpMessage()
{
  Serial.println();
  Serial.print("Encrypted output message: ");
  for (int i = 0; i < 16; i++)
  {
    char str[3];
    sprintf(str, "%02x", encryptedOutputMessage[i]);
    Serial.print(str);
  }
}

void displayDecryptedOutputMessage()
{
  Serial.println();
  Serial.print("Decrypted output message: ");
  for (int i = 0; i < 16; i++)
  {
    Serial.print((char)decryptedOutputMessage[i]);
  }
}