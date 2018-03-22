#pragma once

// AES
namespace crypto
{

	/*
	Keys mentioned in Content Archive Authoring library
	private RsaKey m_NcaHeader1SignKey;
	private RsaKey m_AcidSignKey;
	private RsaKey m_NrrCertificateSignKey;
	private AesKey m_ProdKeyAreaEncryptionKey;
	private AesKey m_ProdNcaHeaderEncryptionKek;
	private RsaKey m_ProdXciHeaderSignKey;
	private AesKey m_ProdXciInitialDataEncryptionKey;
	private AesKey m_ProdTitleKeyGenarateKey;
	private AesKey m_ProdETicketCommonKey;
	private RsaKey m_ProdETicketSignKey;
	*/
	namespace aes
	{

		/*
		public static AesKey GetNcaExternalContentKey(IHashCalculator hashCalculator, ulong titleId)
		{
			Trace.Assert(hashCalculator != null, "IHashCalculator is null.");
			byte[] array = BitConverter.GetBytes(titleId).Reverse<byte>().ToArray<byte>();
			byte[] numArray = new byte[hashCalculator.HashSize];
			hashCalculator.CalculateHash(array, 0, (int)array.Length, numArray, 0);
			return new AesKey(((IEnumerable<byte>)numArray).Where<byte>((byte name, int index) => index < 16).ToArray<byte>());
		}
		*/
		namespace nx
		{
			enum Aes128KeyId
			{
				NcaContentKey,
				NcaHeader,
				XciInitialData,
				XciHeader,
				ETicketCommonKey
			};

			enum HmacSha256KeyId
			{
				TitleKeyGenarateKey
			};

			namespace dev
			{
				// aes128-xts keys (seem to use 512 block sizes, aka 0x200 blocks)
				byte_t nca_body_key[2][16] =
				{
					{ 0xE5, 0x64, 0xDB, 0xFE, 0x52, 0x93, 0x3A, 0x65, 0x3C, 0x8B, 0x5E, 0xF8, 0x2C, 0x9D, 0xF4, 0xB5 },
					{ 0x60, 0x7B, 0x77, 0x3E, 0x31, 0xE9, 0x6A, 0x8F, 0x8E, 0x44, 0x5C, 0x98, 0x71, 0xC0, 0x57, 0xDB },
				};

				byte_t nca_header_key[2][16] =
				{
					{ 0xCB, 0x9A, 0x93, 0x9F, 0x82, 0x72, 0x54, 0x4A, 0x74, 0x5D, 0x28, 0x46, 0x9D, 0xCC, 0x38, 0x12 },
					{ 0x06, 0x31, 0x27, 0x06, 0xAE, 0x62, 0x56, 0x8C, 0x5B, 0x7E, 0xE6, 0x9F, 0x7E, 0x01, 0x02, 0x24 },
				};

				// aeskey, related to m_KeyAreaEncryptionKeyList (first in list?)
				byte_t key_area_encryption_key_0[0x10] = { 0x3A, 0x7C, 0x3E, 0x38, 0x4A, 0x8F, 0x22, 0xFF, 0x4B, 0x21, 0x57, 0x19, 0xB7, 0x81, 0xAD, 0x0C };

				byte_t titlekey_generate_key[0x20] = { 39, 111, 56, 188, 68, 106, 241, 86, 31, 44, 90, 111, 116, 32, 93, 197, 25, 181, 59, 188, 178, 159, 211, 175, 212, 178, 162, 4, 28, 152, 117, 126 };

				// aes128-cbc keys
				byte_t xci_header_key[16] = { 0x01, 0xc5, 0x8f, 0xe7, 0x2d, 0x13, 0x5a, 0xb2, 0x9a, 0x3f, 0x69, 0x33, 0x95, 0x74, 0xb1 };
				byte_t eticket_common_key[16] = { 0x55, 0xA3, 0xF8, 0x72, 0xBD, 0xC8, 0x0C, 0x55, 0x5A, 0x65, 0x43, 0x81, 0x13, 0x9E, 0x15, 0x3B }; // lol this 3ds dev common key

				byte_t wii_sd_key[16] = { 0xAB, 0x01, 0xB9, 0xD8, 0xE1, 0x62, 0x2B, 0x08, 0xAF, 0xBA, 0xD8, 0x4D, 0xBF, 0xC2, 0xA5, 0x5D };
			}

			namespace prod
			{
				// encrypted with ProdNcaHeaderEncryptionKek
				byte_t nca_enc_header_key[2][16] =
				{
					{ 0x5A, 0x3E, 0xD8, 0x4F, 0xDE, 0xC0, 0xD8, 0x26, 0x31, 0xF7, 0xE2, 0x5D, 0x19, 0x7B, 0xF5, 0xD0 },
					{ 0x1C, 0x9B, 0x7B, 0xFA, 0xF6, 0x28, 0x18, 0x3D, 0x71, 0xF6, 0x4D, 0x73, 0xF1, 0x50, 0xB9, 0xD2 }
				};

				byte_t master_key_0[16] = { 0xC2, 0xCA, 0xAF, 0xF0, 0x89, 0xB9, 0xAE, 0xD5, 0x56, 0x94, 0x87, 0x60, 0x55, 0x27, 0x1C, 0x7D };

				byte_t nca_header_key[2][16] = 
				{
					{ 0xAE, 0xAA, 0xB1, 0xCA, 0x08, 0xAD, 0xF9, 0xBE, 0xF1, 0x29, 0x91, 0xF3, 0x69, 0xE3, 0xC5, 0x67 },
					{ 0xD6, 0x88, 0x1E, 0x4E, 0x4A, 0x6A, 0x47, 0xA5, 0x1F, 0x6E, 0x48, 0x77, 0x06, 0x2D, 0x54, 0x2D }
				};

				byte_t xci_header_key[16] = { 0x01, 0xC5, 0x8F, 0xE7, 0x00, 0x2D, 0x13, 0x5A, 0xB2, 0x9A, 0x3F, 0x69, 0x33, 0x95, 0x74, 0xB1 };
			}

			
			
		}
	}

	// RSA
	namespace rsa
	{
		namespace nx
		{
			enum Rsa2048PssKeyId // sign/validate
			{
				NcaHeader1, // also reference as "sign key data"
				Acid,
				NrrCertificate
			};

			enum Rsa2048Pkcs1KeyId // sign/validate
			{
				XciHeader,
				ETicket // XS00000020 or XS00000021 ident
			};

			enum RsaOaepKeyId // encrypt/decrypt
			{
				XciKeyArea
			};

			/*
			in regards to etickets
			%llx....string too long.invalid string position.CT..TW..NG..VP..PC..%08X....Contents of ticket at 0x%0*lx:..  Ticket ID = 0x%I64x...  Version   = %hd...  Rights ID..... %02hhx.....  Device ID = 0x%I64x...  Issuer    = %s....  SigType   = 0x%0x.....  AccountId = 0x%x..  LicenseType = %hhd....  CommonKeyId = %hhd....  PropertyMask = 0x%hx..  Title Key (encrypted and may be personalized):.   ....  sectTotalSize %d..  sectHdrOffset %d..  nSectHdrs %hd.....  nSectHdrEntrySize %hd.....V1 Section Header %d:...  sectOffset %d.....  nRecords %d...  recordSize %d.....  sectionSize %d....PERMANENT...SUBSCRIPTION....CONTENT.CONTENT CONSUMPTION.ACCESS TITLE....Unknown.LIMITED RESOURCE....  sectionType %s....  V1 Section Records:...    refId ..%02hhx ..    refIdAttr %x...    limit %x....    offset %x...    accessMask:.....    ....    index %hx...    code %hx....    accessTitleId %I64x.....    accessTitleMask %I64x...  Unknown Record Type %hx............
			*/

			// unknown key "EncryptionKeyData"
			byte_t unk_rsa_key_mod[0x100] = { 0x85, 0xF8, 0x8C, 0x41, 0x8A, 0x2D, 0x96, 0xB3, 0xF3, 0x92, 0xD0, 0x6C, 0x9D, 0x90, 0x96, 0x7F, 0x1A, 0x78, 0xD8, 0x17, 0x7A, 0xB8, 0xEC, 0x0E, 0x6E, 0x10, 0x55, 0xC8, 0xCA, 0x7F, 0x18, 0xC7, 0x18, 0x94, 0x75, 0x0D, 0xBA, 0x19, 0x44, 0xDE, 0xFA, 0x93, 0xC8, 0xCB, 0x5F, 0xCA, 0x9B, 0x09, 0x3C, 0x2E, 0x2D, 0x12, 0xB2, 0xFA, 0x0B, 0xB7, 0xC0, 0xFC, 0xD4, 0x05, 0xC4, 0x2B, 0xC7, 0x9F, 0x6A, 0xAC, 0xB5, 0x80, 0xA0, 0x4E, 0x72, 0xCB, 0x8D, 0x5E, 0x85, 0x63, 0xBF, 0x99, 0x16, 0x89, 0x07, 0xFE, 0x3A, 0x09, 0xBC, 0xDF, 0x5C, 0xF3, 0x90, 0x29, 0x33, 0xFF, 0x72, 0xB5, 0x18, 0xD0, 0x08, 0xEB, 0xC3, 0x98, 0xC2, 0x4C, 0x3B, 0xF6, 0xCF, 0xCC, 0xB2, 0x71, 0xDD, 0x8E, 0xEE, 0x13, 0x88, 0x82, 0x79, 0x67, 0xC1, 0x6C, 0x3D, 0x60, 0x9C, 0x7D, 0x1D, 0x43, 0x52, 0xF1, 0x48, 0xBB, 0x5D, 0xCB, 0x39, 0xAA, 0x93, 0x8E, 0x75, 0x76, 0xBE, 0x37, 0x47, 0x9C, 0xAB, 0x2F, 0x22, 0xBF, 0xCA, 0x75, 0xC3, 0x50, 0x99, 0xD4, 0x98, 0x72, 0xC2, 0x62, 0x58, 0xA3, 0xB9, 0xD3, 0xD7, 0xCF, 0xEA, 0x40, 0x02, 0x42, 0x49, 0xC9, 0xBA, 0xFE, 0x83, 0x87, 0x40, 0xF7, 0x87, 0x6A, 0x4D, 0x5A, 0xB7, 0x6F, 0x0C, 0x3C, 0xD7, 0x6C, 0x8B, 0x00, 0x68, 0x65, 0x32, 0x29, 0x70, 0x68, 0x26, 0x91, 0x14, 0x04, 0x58, 0x2A, 0xE8, 0x01, 0x68, 0x41, 0x89, 0x58, 0x87, 0xA3, 0x1D, 0xE4, 0xB9, 0xBF, 0x8B, 0x9C, 0x47, 0x88, 0xA6, 0x79, 0x5A, 0x17, 0xC4, 0xE3, 0xAB, 0x05, 0xA8, 0x31, 0x1E, 0xD1, 0x55, 0xA2, 0xA2, 0x04, 0x85, 0xF1, 0x96, 0x81, 0x23, 0x04, 0x44, 0x57, 0xCC, 0x93, 0x66, 0x0D, 0xC1, 0x9E, 0x34, 0x46, 0x29, 0x12, 0xCD, 0x74, 0x19, 0xCD, 0x1F, 0xD4, 0x26, 0x31, 0xAB, 0xC5 };
			byte_t unk_rsa_key_d[0x100] = { 0x1B, 0xC9, 0x6E, 0x85, 0xD5, 0x7C, 0x19, 0x2A, 0xDF, 0xD5, 0x4E, 0xA7, 0x88, 0x92, 0xC9, 0xB4, 0x39, 0x30, 0x61, 0x59, 0x95, 0x59, 0xAF, 0x94, 0x5A, 0x9D, 0xC6, 0xBD, 0x2B, 0xCA, 0xEA, 0xBF, 0xB8, 0xC8, 0x69, 0xF2, 0xDB, 0xEB, 0x8B, 0xCE, 0x57, 0xD8, 0xB9, 0x27, 0xFD, 0x89, 0x4F, 0x58, 0xBE, 0x03, 0xB1, 0xD3, 0x94, 0x0D, 0xAA, 0xCA, 0x85, 0x1B, 0xAB, 0x7A, 0x3A, 0xB2, 0xFD, 0xE7, 0x81, 0xBF, 0xAA, 0xB1, 0xB0, 0x0E, 0x35, 0x5F, 0x24, 0xC6, 0x3B, 0x12, 0x72, 0x55, 0xF5, 0x47, 0x9C, 0xC1, 0xCD, 0x15, 0xE1, 0xF7, 0xCE, 0x16, 0xB2, 0x8A, 0xE9, 0x3F, 0x0D, 0x72, 0xA4, 0x5F, 0xD9, 0xC9, 0xD4, 0xBA, 0xE5, 0x69, 0xDC, 0x72, 0x17, 0xAD, 0x94, 0x41, 0x6B, 0xBB, 0xCE, 0x83, 0x7C, 0xA7, 0xDB, 0x38, 0x7A, 0xF4, 0xD1, 0x52, 0x2D, 0x83, 0x01, 0xC3, 0xC9, 0xFB, 0x43, 0xA3, 0x54, 0x41, 0x3D, 0xBD, 0x78, 0x04, 0x97, 0x9D, 0xA6, 0xAE, 0x1D, 0x34, 0x5E, 0xD6, 0x77, 0x70, 0x08, 0xE4, 0xD6, 0x7F, 0x98, 0x72, 0x1A, 0xF2, 0xFF, 0xAF, 0x86, 0x5E, 0x05, 0x40, 0xA3, 0x51, 0x97, 0x6E, 0x30, 0xBD, 0x06, 0xDF, 0xC1, 0xF7, 0x58, 0xC2, 0x3C, 0x8D, 0x49, 0xAE, 0x13, 0x7D, 0x1E, 0x27, 0x98, 0x92, 0x47, 0xD0, 0x55, 0x62, 0x08, 0x17, 0x34, 0xEB, 0xC5, 0x68, 0x43, 0xFB, 0x6F, 0xA5, 0x3F, 0x28, 0x3A, 0xBB, 0x37, 0x2B, 0xAD, 0xF7, 0x0F, 0x85, 0xB1, 0xDF, 0x6C, 0xC9, 0x9F, 0x85, 0x46, 0xF7, 0x50, 0xC4, 0x87, 0xA1, 0xD4, 0xAA, 0xCB, 0x01, 0x85, 0xFA, 0xC6, 0x79, 0x01, 0x2C, 0x0B, 0x2F, 0xEE, 0x71, 0xFE, 0x5D, 0x86, 0x17, 0xE5, 0x91, 0x5F, 0x44, 0x79, 0x6D, 0xC3, 0x89, 0xE3, 0x8A, 0xDD, 0x03, 0xD4, 0xCA, 0xEA, 0x79, 0xCB, 0x34, 0x61, 0xE7, 0x53, 0x41 };

			// rsa2048-pkcs1-sha256 keys
			byte_t XS00000020_d[0x100] = { 0x51, 0x02, 0x71, 0x58, 0xCA, 0x69, 0xD9, 0x61, 0x3A, 0x81, 0xDE, 0x76, 0x55, 0xBB, 0xCE, 0xEA, 0x40, 0xE9, 0x9E, 0x66, 0xC7, 0xD5, 0x36, 0x36, 0x8D, 0xD3, 0xCC, 0x75, 0xAF, 0x08, 0x23, 0x9A, 0x8B, 0x07, 0xB0, 0xF4, 0xA8, 0xC9, 0xB6, 0x52, 0xC3, 0xEF, 0x00, 0x4D, 0x0A, 0x58, 0x4F, 0xA2, 0x70, 0xA3, 0xD1, 0x98, 0xE8, 0x56, 0x3B, 0x01, 0x27, 0x4C, 0x1F, 0x97, 0x2F, 0x01, 0x44, 0x86, 0x1C, 0xA9, 0x61, 0x64, 0xDF, 0x73, 0x9E, 0xAA, 0x83, 0x00, 0xA3, 0x97, 0xB9, 0x81, 0xEC, 0x13, 0xCC, 0x8E, 0x34, 0xC3, 0xCC, 0x8F, 0xF7, 0x5E, 0x61, 0xF1, 0xB2, 0x8C, 0x3D, 0xEC, 0xE9, 0x09, 0x54, 0xAA, 0x2C, 0xF4, 0xE8, 0xBC, 0xE5, 0x74, 0x4D, 0x75, 0x97, 0x12, 0xD0, 0x64, 0xFB, 0xB0, 0xAB, 0x9F, 0xE5, 0x2C, 0xE0, 0xDF, 0xD9, 0x3E, 0x89, 0xEB, 0xB7, 0x43, 0xD0, 0xD2, 0x88, 0xD6, 0xE4, 0xB3, 0xD4, 0xC9, 0x23, 0x67, 0xE0, 0xF5, 0xC4, 0x98, 0xDF, 0x4E, 0x12, 0x64, 0x53, 0xC3, 0x92, 0xEB, 0x77, 0x72, 0xDC, 0x83, 0xBF, 0x11, 0xCD, 0x4B, 0x05, 0x1D, 0x43, 0x1C, 0x6A, 0x7D, 0x9F, 0x00, 0x1E, 0x1A, 0xB7, 0x50, 0x03, 0x0A, 0xF0, 0x8C, 0x67, 0x52, 0x7F, 0x3E, 0xAD, 0x72, 0xC4, 0x39, 0x93, 0x3A, 0xB1, 0x66, 0xFC, 0x5F, 0x84, 0xCF, 0x1D, 0x0F, 0x47, 0xDC, 0x7A, 0xDC, 0xEE, 0xAB, 0xB5, 0x5A, 0x44, 0x04, 0x5A, 0xA8, 0x0E, 0x07, 0xF4, 0xED, 0xDF, 0x56, 0x47, 0xCF, 0x8B, 0xDE, 0xA6, 0x26, 0x3C, 0x89, 0xD0, 0xDB, 0xDD, 0xED, 0xD8, 0xF2, 0xA9, 0x76, 0x95, 0x7D, 0xA5, 0xDB, 0xD2, 0x8F, 0x8E, 0xF2, 0x31, 0xC7, 0x6A, 0xFB, 0x9F, 0xA4, 0xA7, 0x95, 0xE0, 0xBF, 0x5F, 0x57, 0x48, 0x3C, 0x65, 0x60, 0x2A, 0x46, 0x2A, 0xDD, 0xA8, 0x58, 0xD8, 0x2F, 0x89, 0x81 };
			byte_t XS00000020_mod[0x100] = { 0xBA, 0x27, 0x84, 0x28, 0x76, 0x5D, 0x87, 0x9A, 0x7F, 0x21, 0x54, 0x04, 0xC6, 0xEE, 0x4E, 0x0A, 0x0D, 0x3F, 0x66, 0xC3, 0x3B, 0xC7, 0xF8, 0xA3, 0x2F, 0xD8, 0x98, 0xE5, 0x2C, 0xB7, 0xB6, 0x34, 0x43, 0xCE, 0xD8, 0xB0, 0x05, 0x27, 0xD8, 0x9D, 0xED, 0xC6, 0xBB, 0xF6, 0x0A, 0xD1, 0xC5, 0xC9, 0x92, 0x30, 0x21, 0xDD, 0x55, 0x5F, 0x9B, 0xAD, 0x4B, 0xE0, 0xC0, 0xC4, 0x06, 0xD3, 0x70, 0x29, 0x15, 0xE5, 0xB3, 0x4A, 0xC2, 0xD2, 0xAB, 0xE5, 0x03, 0xC3, 0x2A, 0x3A, 0x23, 0xB4, 0x38, 0x34, 0xC9, 0x15, 0x7B, 0x9A, 0x0A, 0xF2, 0xE4, 0xE9, 0xC0, 0x3B, 0xED, 0xE2, 0xB4, 0xC1, 0x15, 0xF5, 0x35, 0x3D, 0xFC, 0x66, 0xBD, 0x04, 0xA6, 0xC0, 0x79, 0x97, 0x0E, 0x38, 0xCB, 0xDD, 0x5A, 0x50, 0xA2, 0xB9, 0x8F, 0xF2, 0xD7, 0x65, 0xFC, 0xF8, 0x33, 0x81, 0xE9, 0xE0, 0xE8, 0x49, 0xC3, 0x57, 0x35, 0x78, 0x37, 0x8F, 0xF6, 0x59, 0x51, 0x61, 0x3E, 0x95, 0xF7, 0x5E, 0xE8, 0xEF, 0x26, 0x18, 0x3A, 0x40, 0xAA, 0xE4, 0xA7, 0x6D, 0x73, 0x84, 0xEA, 0x47, 0x8D, 0x2C, 0xDC, 0xE8, 0x0F, 0xBA, 0x03, 0x21, 0xA6, 0xBF, 0x8D, 0x69, 0x98, 0x3C, 0x3A, 0xA7, 0xAE, 0x54, 0x43, 0xB7, 0x2B, 0xFE, 0x41, 0x0B, 0xF1, 0x32, 0x3C, 0xBD, 0x88, 0xC3, 0x56, 0x0E, 0xA1, 0x3D, 0x17, 0xD3, 0x8A, 0x2E, 0x34, 0x04, 0x1D, 0xE7, 0xAA, 0xF3, 0x89, 0xDE, 0x43, 0x75, 0x22, 0x5C, 0xA8, 0x7E, 0xE3, 0x49, 0xC7, 0x60, 0xC7, 0xD9, 0x9B, 0xE7, 0xE7, 0x37, 0xC6, 0x26, 0x1C, 0xC7, 0x4E, 0x25, 0xAE, 0x46, 0x52, 0x7A, 0xC9, 0x61, 0x9F, 0x93, 0x90, 0x57, 0x08, 0x8D, 0x74, 0x35, 0xA6, 0xDE, 0x7B, 0x25, 0xAB, 0x82, 0xDD, 0x54, 0x10, 0xF2, 0x57, 0x9C, 0xAE, 0xF1, 0x49, 0x1A, 0x90, 0x9D, 0x30, 0x2B };

			// rsa2048-pss-sha256 keys
			byte_t nca_header1_d[0x100] = { 0x0C, 0x05, 0xB5, 0x6D, 0xE9, 0x0F, 0xE6, 0x41, 0x55, 0x6D, 0x52, 0x36, 0xC8, 0x57, 0xB3, 0x60, 0x57, 0xDB, 0xCD, 0xB3, 0x03, 0x0F, 0x57, 0xF1, 0x17, 0x8A, 0x30, 0x33, 0x8A, 0x68, 0x92, 0xFB, 0x73, 0x57, 0x04, 0x8A, 0xCB, 0xE3, 0xF4, 0x8A, 0xBF, 0xE3, 0xF2, 0xAC, 0x38, 0x23, 0x30, 0x26, 0x95, 0x42, 0x3D, 0x50, 0xFA, 0xB4, 0xAF, 0x60, 0x21, 0x75, 0xDC, 0xD9, 0x57, 0xB4, 0xC3, 0x6C, 0xE5, 0xF6, 0xE5, 0xE0, 0x55, 0x65, 0x77, 0x4B, 0xC7, 0xA6, 0x7E, 0x0A, 0xFE, 0xDD, 0x80, 0x42, 0x4F, 0x0D, 0x7E, 0x15, 0x8D, 0xF4, 0x27, 0x37, 0x24, 0x99, 0xF2, 0x12, 0x31, 0xDB, 0xD7, 0x7F, 0x1E, 0x92, 0x21, 0x14, 0xCA, 0x21, 0xF6, 0x50, 0x08, 0x92, 0xAE, 0x31, 0xDE, 0xF4, 0x29, 0x24, 0xD6, 0x41, 0xB3, 0x47, 0x18, 0x37, 0x14, 0xF9, 0x8D, 0x5D, 0x95, 0xF4, 0xF5, 0x7F, 0x99, 0xFB, 0x86, 0xDA, 0x65, 0xE9, 0x72, 0xA9, 0x77, 0x65, 0xC8, 0xC5, 0x29, 0x5A, 0x19, 0x2B, 0x51, 0x1C, 0x72, 0xEB, 0x49, 0xD1, 0x0B, 0x73, 0x8B, 0x3E, 0x2E, 0xC8, 0x7E, 0xFF, 0xD8, 0xFE, 0xF4, 0xF4, 0xF6, 0x92, 0x27, 0x7F, 0xA0, 0xDB, 0xC1, 0x25, 0xBC, 0xEC, 0x5F, 0x0B, 0x2D, 0x99, 0xEB, 0xDD, 0x9E, 0x5D, 0x42, 0x75, 0xB5, 0xE3, 0x24, 0xCB, 0xE9, 0xEB, 0xD9, 0x00, 0x4B, 0x12, 0x5D, 0xA3, 0xA6, 0x25, 0xAC, 0x20, 0x82, 0x25, 0x53, 0x1F, 0xC6, 0x2F, 0x27, 0xF1, 0x99, 0x7A, 0x99, 0xDC, 0xA5, 0xC0, 0x5E, 0x63, 0x0F, 0x78, 0x03, 0x2A, 0x18, 0xD9, 0xE1, 0x06, 0x3B, 0xDF, 0xB2, 0x95, 0x19, 0x32, 0xB4, 0x65, 0xD2, 0xD0, 0xFE, 0x18, 0xC7, 0x54, 0x5C, 0xA4, 0xF6, 0xD8, 0xFD, 0xDB, 0x6D, 0xD8, 0xDA, 0xF2, 0x9A, 0x55, 0x5C, 0x3E, 0xEC, 0x17, 0x72, 0x09, 0xA3, 0x1A, 0x0A, 0xC1 };
			byte_t nca_header1_mod[0x100] = { 0xD8, 0xF1, 0x18, 0xEF, 0x32, 0x72, 0x4C, 0xA7, 0x47, 0x4C, 0xB9, 0xEA, 0xB3, 0x04, 0xA8, 0xA4, 0xAC, 0x99, 0x08, 0x08, 0x04, 0xBF, 0x68, 0x57, 0xB8, 0x43, 0x94, 0x2B, 0xC7, 0xB9, 0x66, 0x49, 0x85, 0xE5, 0x8A, 0x9B, 0xC1, 0x00, 0x9A, 0x6A, 0x8D, 0xD0, 0xEF, 0xCE, 0xFF, 0x86, 0xC8, 0x5C, 0x5D, 0xE9, 0x53, 0x7B, 0x19, 0x2A, 0xA8, 0xC0, 0x22, 0xD1, 0xF3, 0x22, 0x0A, 0x50, 0xF2, 0x2B, 0x65, 0x05, 0x1B, 0x9E, 0xEC, 0x61, 0xB5, 0x63, 0xA3, 0x6F, 0x3B, 0xBA, 0x63, 0x3A, 0x53, 0xF4, 0x49, 0x2F, 0xCF, 0x03, 0xCC, 0xD7, 0x50, 0x82, 0x1B, 0x29, 0x4F, 0x08, 0xDE, 0x1B, 0x6D, 0x47, 0x4F, 0xA8, 0xB6, 0x6A, 0x26, 0xA0, 0x83, 0x3F, 0x1A, 0xAF, 0x83, 0x8F, 0x0E, 0x17, 0x3F, 0xFE, 0x44, 0x1C, 0x56, 0x94, 0x2E, 0x49, 0x83, 0x83, 0x03, 0xE9, 0xB6, 0xAD, 0xD5, 0xDE, 0xE3, 0x2D, 0xA1, 0xD9, 0x66, 0x20, 0x5D, 0x1F, 0x5E, 0x96, 0x5D, 0x5B, 0x55, 0x0D, 0xD4, 0xB4, 0x77, 0x6E, 0xAE, 0x1B, 0x69, 0xF3, 0xA6, 0x61, 0x0E, 0x51, 0x62, 0x39, 0x28, 0x63, 0x75, 0x76, 0xBF, 0xB0, 0xD2, 0x22, 0xEF, 0x98, 0x25, 0x02, 0x05, 0xC0, 0xD7, 0x6A, 0x06, 0x2C, 0xA5, 0xD8, 0x5A, 0x9D, 0x7A, 0xA4, 0x21, 0x55, 0x9F, 0xF9, 0x3E, 0xBF, 0x16, 0xF6, 0x07, 0xC2, 0xB9, 0x6E, 0x87, 0x9E, 0xB5, 0x1C, 0xBE, 0x97, 0xFA, 0x82, 0x7E, 0xED, 0x30, 0xD4, 0x66, 0x3F, 0xDE, 0xD8, 0x1B, 0x4B, 0x15, 0xD9, 0xFB, 0x2F, 0x50, 0xF0, 0x9D, 0x1D, 0x52, 0x4C, 0x1C, 0x4D, 0x8D, 0xAE, 0x85, 0x1E, 0xEA, 0x7F, 0x86, 0xF3, 0x0B, 0x7B, 0x87, 0x81, 0x98, 0x23, 0x80, 0x63, 0x4F, 0x2F, 0xB0, 0x62, 0xCC, 0x6E, 0xD2, 0x46, 0x13, 0x65, 0x2B, 0xD6, 0x44, 0x33, 0x59, 0xB5, 0x8F, 0xB9, 0x4A, 0xA9 };
			byte_t nrr_certificate_d[0x100] = { 0x2C, 0x5E, 0x97, 0x84, 0x97, 0x13, 0x8C, 0xD7, 0xFC, 0x6F, 0x36, 0xC1, 0xC1, 0x2A, 0x87, 0x4B, 0xE0, 0x86, 0xD2, 0xFA, 0xB8, 0x97, 0x77, 0xCF, 0xBB, 0xE8, 0x89, 0x58, 0x28, 0xD9, 0xC0, 0xD8, 0x81, 0x7E, 0x1E, 0x67, 0x16, 0x95, 0xCF, 0x14, 0x24, 0x82, 0xB4, 0xE7, 0x92, 0x08, 0xB4, 0xA7, 0x88, 0xC7, 0xC6, 0x8E, 0x32, 0x1C, 0xE4, 0xBB, 0x39, 0x03, 0xA2, 0xDE, 0x21, 0x9D, 0xB8, 0xA1, 0x69, 0x36, 0x36, 0x9D, 0x11, 0x24, 0xCD, 0xB1, 0x48, 0x6B, 0xD3, 0x4B, 0x4F, 0x9E, 0x38, 0x91, 0xD8, 0xFA, 0xDC, 0x00, 0x67, 0x11, 0xE4, 0xBA, 0x54, 0xC7, 0x47, 0x54, 0xFB, 0x55, 0x2A, 0x41, 0xAD, 0x4F, 0x9F, 0x6D, 0x03, 0xF5, 0xEC, 0x4B, 0x42, 0x78, 0xE2, 0xCD, 0x6E, 0x04, 0xFB, 0x5D, 0x20, 0x94, 0x52, 0xAA, 0xFD, 0x58, 0x3A, 0x85, 0x58, 0x31, 0xAE, 0xDE, 0x16, 0xBE, 0x42, 0x22, 0x85, 0xA1, 0x42, 0xBD, 0xBB, 0xA0, 0x87, 0xEB, 0x3B, 0x25, 0x0F, 0x15, 0x5A, 0xA1, 0x0F, 0x53, 0x0E, 0x51, 0xF5, 0xF0, 0xDB, 0x8E, 0xCC, 0x82, 0x4A, 0x4E, 0x67, 0x5D, 0xC1, 0x4C, 0x62, 0x1A, 0x1D, 0x5E, 0x4A, 0xC4, 0xF3, 0x1D, 0xE6, 0x89, 0x83, 0xCB, 0x00, 0xD0, 0x26, 0xFB, 0x62, 0xF1, 0xD9, 0xC6, 0x18, 0x68, 0x16, 0xF6, 0x35, 0xEE, 0x74, 0xE8, 0xEA, 0xD1, 0xCE, 0x8A, 0xE1, 0x83, 0xDA, 0xE0, 0x30, 0x5F, 0x84, 0x43, 0x0D, 0x10, 0xAB, 0x04, 0x5F, 0x0E, 0xDD, 0x9B, 0xEE, 0x17, 0x73, 0x86, 0x70, 0x32, 0x9A, 0x96, 0xAB, 0x09, 0x54, 0xA7, 0x30, 0x25, 0x41, 0x94, 0xE1, 0x5F, 0x03, 0x4F, 0xEA, 0xBA, 0x7D, 0x2B, 0x9A, 0x41, 0x1C, 0x50, 0x5F, 0x2B, 0xDD, 0x83, 0xFA, 0xF4, 0xEF, 0x57, 0x50, 0xD2, 0x7E, 0xB4, 0x9F, 0x89, 0x84, 0x52, 0x37, 0x63, 0x82, 0x02, 0x69, 0x51 };
			byte_t nrr_certificate_mod[0x100] = { 0xC1, 0x15, 0x7C, 0x02, 0x26, 0xE5, 0x35, 0x6F, 0x99, 0xDB, 0xBE, 0xBD, 0xD7, 0x01, 0x07, 0x1C, 0xC2, 0x3D, 0x1E, 0x6B, 0x7E, 0x08, 0x07, 0xBC, 0xE2, 0x6D, 0x49, 0xEC, 0x0B, 0xFF, 0xE4, 0x91, 0x8C, 0x62, 0xB9, 0xFC, 0x69, 0xBF, 0x3A, 0xB6, 0x6C, 0x3A, 0x5D, 0x0E, 0x31, 0x5E, 0x6C, 0x1D, 0x9A, 0x21, 0xD9, 0x9D, 0xD3, 0xB8, 0x50, 0x5F, 0x27, 0x7C, 0x4A, 0xD2, 0xFE, 0xE8, 0xDA, 0x1C, 0xB9, 0x9E, 0x7E, 0x1E, 0x2F, 0x7D, 0xF9, 0x70, 0xA2, 0x98, 0x19, 0x6A, 0x53, 0x40, 0x64, 0xE7, 0xC0, 0x92, 0xAE, 0x64, 0xD2, 0x01, 0xB2, 0x49, 0x30, 0x19, 0x7F, 0xF8, 0x6E, 0x0D, 0x49, 0x35, 0xE9, 0x95, 0x77, 0x00, 0x65, 0xC5, 0x1E, 0xF5, 0x2A, 0xF9, 0xA1, 0x52, 0xA0, 0xA4, 0xFA, 0x87, 0x3D, 0x8F, 0x51, 0xEC, 0x02, 0x80, 0xA4, 0xC7, 0x22, 0x74, 0xEF, 0x56, 0x61, 0x71, 0x39, 0xE2, 0x2F, 0x03, 0x82, 0xDB, 0x50, 0xE9, 0xCC, 0x60, 0x48, 0x46, 0x71, 0xE2, 0xC6, 0x71, 0xF3, 0xF9, 0x85, 0x52, 0x1A, 0xE2, 0xA8, 0x18, 0x77, 0x86, 0xD0, 0x12, 0xEB, 0x4F, 0x81, 0xA0, 0xDF, 0x20, 0x42, 0xF0, 0xF8, 0xE3, 0x00, 0xE6, 0xFC, 0xA7, 0x44, 0xF0, 0xDC, 0x2B, 0x5B, 0xA0, 0xD3, 0x01, 0x34, 0xD0, 0xD7, 0xFD, 0xEF, 0x66, 0x92, 0xB3, 0x87, 0x64, 0xD9, 0x76, 0xDA, 0x6E, 0x3A, 0x19, 0x98, 0x1F, 0xBD, 0x1F, 0x25, 0x69, 0x9F, 0x28, 0xE6, 0x9E, 0xB7, 0x38, 0x92, 0x12, 0x16, 0xDE, 0xDA, 0xE2, 0xB9, 0x7E, 0xFA, 0x98, 0x94, 0xF4, 0x9A, 0xDF, 0x2D, 0xC0, 0x99, 0x83, 0x61, 0xAD, 0xB8, 0x3E, 0x27, 0x3F, 0x0E, 0xB8, 0x9E, 0x9B, 0x11, 0x78, 0xF1, 0x06, 0x30, 0x5B, 0xCA, 0xF4, 0xEB, 0x72, 0x20, 0xD3, 0x15, 0x15, 0xC0, 0xC7, 0x1A, 0x08, 0xAE, 0x6E, 0xB2, 0x02, 0x43, 0xE9 };

			// rsa2048-oaep-sha256 key
			byte_t xci_keyarea_labledigest[0x20] = { 0xB1, 0x7B, 0x5F, 0x65, 0x0E, 0x75, 0x90, 0xED, 0xFE, 0x3A, 0xF0, 0x75, 0x0B, 0x92, 0x05, 0xB3, 0x0E, 0x7D, 0x49, 0x89, 0x24, 0xD8, 0xE3, 0x85, 0xCB, 0x40, 0xE0, 0xE7, 0xF8, 0xDE, 0xF0, 0x77 };
			byte_t xci_keyarea_mod[0x100] = { 0xA6, 0x1A, 0x3F, 0x5E, 0x16, 0x94, 0x4D, 0x5F, 0x88, 0x07, 0x45, 0x92, 0x42, 0x02, 0x5C, 0xF8, 0xF8, 0x01, 0xA6, 0x8F, 0xF0, 0x77, 0x76, 0x06, 0x06, 0x4B, 0x67, 0x02, 0x35, 0x2F, 0xC2, 0xF6, 0xCD, 0x74, 0xBC, 0x57, 0x36, 0xA0, 0x61, 0x1D, 0xD6, 0x66, 0x35, 0x79, 0x6E, 0xB7, 0xFF, 0xC1, 0x05, 0xC6, 0x59, 0xD9, 0x1E, 0xC9, 0xC3, 0x1F, 0x5B, 0x17, 0xA9, 0x24, 0x46, 0xB3, 0xAB, 0x1D, 0x7B, 0x79, 0xA8, 0xF2, 0x80, 0xC8, 0x6F, 0xA7, 0x9B, 0x2D, 0xE8, 0xBF, 0x91, 0xD7, 0xD4, 0xA2, 0x07, 0x53, 0x98, 0x82, 0x7D, 0x91, 0x8A, 0x68, 0x79, 0x9B, 0xB6, 0x8F, 0xA7, 0x05, 0x7B, 0x2B, 0x6C, 0x09, 0x2A, 0x58, 0x8A, 0x21, 0xE5, 0xB6, 0xCD, 0xAC, 0xCB, 0x84, 0x5F, 0x22, 0x16, 0x82, 0x54, 0x14, 0x03, 0xEB, 0xBB, 0x86, 0xEC, 0x59, 0x36, 0x38, 0xF8, 0x41, 0x41, 0xCA, 0x23, 0x8A, 0xF2, 0x98, 0x01, 0xAD, 0x14, 0xB6, 0x65, 0x15, 0x3B, 0x63, 0x42, 0xC1, 0x3E, 0x55, 0x8C, 0xC2, 0x38, 0x4E, 0xC0, 0x57, 0x5E, 0xFA, 0x2A, 0x2C, 0xC7, 0x9C, 0xBE, 0x5C, 0xD7, 0x56, 0x4D, 0xCF, 0x36, 0x31, 0x93, 0xD2, 0xB1, 0x0A, 0x8C, 0x7C, 0x7F, 0xFE, 0x46, 0x20, 0xE3, 0x91, 0x7C, 0x63, 0x3F, 0x24, 0x81, 0xFF, 0x4C, 0x68, 0x4F, 0xBE, 0x16, 0x68, 0x66, 0x1C, 0x90, 0xCD, 0xFE, 0x8D, 0xC5, 0x63, 0x3B, 0x2D, 0x5C, 0x25, 0x95, 0xA8, 0x4B, 0x3C, 0xAF, 0x57, 0x07, 0x84, 0x31, 0x37, 0xFA, 0x63, 0x98, 0x1B, 0xAC, 0xB2, 0x81, 0xB1, 0x29, 0x67, 0x0A, 0x31, 0x3D, 0x7E, 0x2D, 0x7F, 0xFE, 0xA5, 0x29, 0x3D, 0xBF, 0xD3, 0xCC, 0x9D, 0x73, 0x75, 0x40, 0x8B, 0x79, 0x98, 0x39, 0x8A, 0xAD, 0x90, 0x65, 0x82, 0x90, 0x09, 0xA4, 0x74, 0xA2, 0x3F, 0xEE, 0xC7, 0x75, 0x06, 0x29, 0x85 };

		}
		
	}
	
}
