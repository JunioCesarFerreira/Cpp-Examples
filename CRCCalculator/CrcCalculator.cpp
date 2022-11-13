#include <iostream>
#include <stdint.h>

//-----------------------------------------------------------------------------------------------------------------------------------
// Classe de cômputo do CRC (Cyclic Redundancy Check)
//-----------------------------------------------------------------------------------------------------------------------------------
template<class data_t>
class CrcClass
{
	private:
		bool input_reflected;  // Indica se entrada é refletida.
		bool result_reflected; // Indica se resultado é refletido.
		data_t div_polynomial; // Polinômio divisor.
		data_t init_value;	 // Valor inicial para cômputo do CRC.
		data_t msbMask;		// Mascara de teste de bit mais significativo.
		uint8_t shift_bits;	// Deslocamento de bits para cômputo do CRC sobre os dados de entrada.
				
		// Reflete bits		
		inline data_t reflect_bits(data_t value)
		{
			data_t tmp = value & 1;
			for (size_t i=1; i < sizeof(value)*8; i++)
			{
				tmp <<= 1;
				value >>= 1;
				tmp |= 1 & value; 
			}
			return tmp;
		}
		
		inline data_t calc_with_reflected_input(char* data, size_t length)
		{
			data_t crc = init_value;
			for (uint8_t i=0; i<length; i++) 
			{
				uint8_t curr_byte = data[i]; // Variável auxiliar de verificação do bit mais significativo.
				for (int j=0; j<8; j++) 
				{
					if ((curr_byte^crc) & msbMask != 0)
					{
						crc = (crc >> 1) ^ div_polynomial;
					}
					else crc >>= 1;		 
					curr_byte >>= 1;
				}
			}
			return crc;
		}
		
		inline data_t calc_without_reflected_input(char* data, size_t length)
		{
			data_t crc = init_value;
			for (uint8_t i=0; i<length; i++) 
			{
				crc ^= (data_t)data[i] << shift_bits;
				for (int i = 0; i < 8; i++)
				{
					if ((crc & msbMask) != 0)
					{			
						crc = (crc << 1) ^ div_polynomial;
					}
					else crc <<= 1;
				}
			}
			return crc;
		}
		
	public:
		// Construtor
		CrcClass(data_t polynomial, data_t init, bool input_ref, bool result_ref)
		{
			changeParameters(polynomial, init, input_ref, result_ref);
		}
		
		// Carrega parâmetros de cômputo do CRC
		void changeParameters(data_t polynomial, data_t init, bool input_ref, bool result_ref)
		{
			input_reflected = input_ref;
			result_reflected = result_ref;
			if (input_reflected)
			{
				div_polynomial = reflect_bits(polynomial);
				init_value = reflect_bits(init);
				msbMask = 1;
				shift_bits = 0;
			}
			else
			{
				div_polynomial = polynomial;
				init_value = init;	
				msbMask = 1 << (8*sizeof(polynomial)-1);
				shift_bits = 8*sizeof(polynomial)-8;
			}			
		}
		
		// Calcula CRC utilizando parâmetros do objeto.
		data_t calc(char* data, size_t length)
		{
			data_t crc;
			if (input_reflected) // Entrada refletida
			{
				crc = calc_with_reflected_input(data, length);
			}
			else // Entrada não refletida
			{
				crc = calc_without_reflected_input(data, length);
			}
			
			/*
			Tabela verdade de aplicação de reflexão no resultado:
			input result reflect
			  0	    0	   0
			  0	    1	   1
			  1	    0	   1
			  1	    1	   0
			*/
			if (result_reflected ^ input_reflected) crc = reflect_bits(crc);
			
			return crc;
		}	
};
template class CrcClass<uint8_t>;
template class CrcClass<uint16_t>;
template class CrcClass<uint32_t>;
template class CrcClass<uint64_t>;

//-----------------------------------------------------------------------------------------------------------------------------------
// Programa de testes
//-----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>   
#include <conio.h>

main()
{
	uint8_t sizeArray = 14;
	char testArray[sizeArray] = { 128, '0', '1','2','3','4','5','6','7','8','9', 'a', 'A', 129 };
	
	// Valores verificados com http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
	uint8_t checkedValues8[4] = { 0xF1, 0x8F, 0xC8, 0x13 };
	uint16_t checkedValues16[4] = { 0x6755, 0xAAE6, 0x3100, 0x8C};
	uint32_t checkedValues32[4] = { 0xB8B77646, 0x626EED1D, 0xD26E6139, 0x9C86764B };
	
	printf("Cyclic Redundancy Check Tests\r\n");
	printf("input: %s\r\n", testArray);
	
	printf("\nCRC-8\n");
	
	// Teste com polinômio x^8 + x^2 + x + 1
	uint8_t polynomial_dg8 = 0x7;
	uint8_t initalize8 = 0;
	CrcClass<uint8_t> crc8(polynomial_dg8, initalize8, false, false);
	// Testa todas possibilidades de reflexão.
	for (uint8_t p=0; p<4; p++)
	{
		bool input_reflect = p & 2;
		bool result_reflect = p & 1;
		crc8.changeParameters(0x7, 0, input_reflect, result_reflect);
		uint8_t crc = crc8.calc(testArray, sizeArray);
		printf("result crc: %2x \tchecked value: %2x\n", crc, checkedValues8[p]);		
	}
	
	printf("\nCRC-16\n");
	
	// Teste com polinômio x^16 + x^12 + x^5 + 1
	uint16_t polynomial_dg16 = 0x1021;
	uint16_t initalize16 = 0xFFFF;
	CrcClass<uint16_t> crc16(polynomial_dg16, initalize16, false, false);
	// Testa todas possibilidades de reflexão.
	for (uint8_t p=0; p<4; p++)
	{
		bool input_reflect = p & 2;
		bool result_reflect = p & 1;
		crc16.changeParameters(polynomial_dg16, initalize16, input_reflect, result_reflect);
		uint16_t crc = crc16.calc(testArray, sizeArray);
		printf("result crc: %4x \tchecked value: %4x\n", crc, checkedValues16[p]);	
	}	
	
	printf("\nCRC-32\n");
	
	// Teste com polinômio x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
	uint32_t polynomial_dg32= 0x04C11DB7;
	uint32_t initalize32 =	0xFFFFFFFF;
	CrcClass<uint32_t> crc32(polynomial_dg32, initalize32, false, false);
	// Testa todas possibilidades de reflexão.
	for (uint8_t p=0; p<4; p++)
	{
		bool input_reflect = p & 2;
		bool result_reflect = p & 1;
		crc32.changeParameters(polynomial_dg32, initalize32, input_reflect, result_reflect);
		uint32_t crc = crc32.calc(testArray, sizeArray);
		printf("result crc: %8x \tchecked value: %8x\n", crc, checkedValues32[p]);	
	}
	
	getch();
}
