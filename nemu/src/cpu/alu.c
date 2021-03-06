#include "cpu/cpu.h"

void set_CF_add(uint32_t result,uint32_t src,size_t data_size){
	result=sign_ext(result & (0xFFFFFFFF>>(32-data_size)),data_size);
	src=sign_ext(src & (0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=(result<src);
}

void set_ZF(uint32_t result,size_t data_size){
	result=result&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);
}

void set_SF(uint32_t result, size_t data_size) {
	result = sign_ext(result & (0xFFFFFFFF >> (32 - data_size)), data_size);
	cpu.eflags.SF = sign(result);
}

void set_PF(uint32_t result){
	int n=0;
	uint32_t r;
	for(int i=1;i<9;i++){
		r=result<<(32-i);
		r=r>>31;
		if(r==1)
			n++;
	}
	cpu.eflags.PF=(n==0||n==2||n==4||n==6||n==8);
}

void set_OF_add(uint32_t result, uint32_t src, uint32_t dest, size_t data_size) {
	switch(data_size) {
		case 8:
			result = sign_ext(result & 0xFF, 8);
			src = sign_ext(src & 0xFF, 8);
			dest = sign_ext(dest & 0xFF, 8);
			break;
		case 16:
			result = sign_ext(result & 0xFFFF, 16);
			src = sign_ext(src & 0xFFFF, 16);
			dest = sign_ext(dest & 0xFFFF, 16);
			break;
		default: break;
	}
	if(sign(src) == sign(dest)) {
		if(sign(src) != sign(result))
			cpu.eflags.OF = 1;
		else
			cpu.eflags.OF = 0;
	} else {
		cpu.eflags.OF = 0;
	}
}

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = dest + src;

	set_CF_add(res, src, data_size);
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

void set_CF_adc(uint32_t result, uint32_t src, size_t data_size){
	result = sign_ext(result&(0xFFFFFFFF>>(32-data_size)),data_size);
	src = sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF)
		cpu.eflags.CF = result<=src;
	else
		cpu.eflags.CF = result<src;
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = dest + src + cpu.eflags.CF;

	set_CF_adc(res, src, data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_add(res,src,dest,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

void set_CF_sub(uint32_t src, uint32_t dest, size_t data_size){
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)),data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)),data_size);
	cpu.eflags.CF=src>dest;
}

void set_OF_sub(uint32_t result, uint32_t src, uint32_t dest, size_t data_size){
	switch(data_size) {
		case 8:
			result = sign_ext(result & 0xFF, 8);
			src = sign_ext(src & 0xFF, 8);
			dest = sign_ext(dest & 0xFF, 8);
			break;
		case 16:
			result = sign_ext(result & 0xFFFF, 16);
			src = sign_ext(src & 0xFFFF, 16);
			dest = sign_ext(dest & 0xFFFF, 16);
			break;
		default: break;
	}
	if(sign(src)!=sign(dest)&&sign(src)==sign(result))
		cpu.eflags.OF=1;
	else
		cpu.eflags.OF=0;
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = dest - src;

	set_CF_sub(src, dest, data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

void set_CF_sbb(uint32_t src, uint32_t dest, size_t data_size){
	src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)),data_size);
	dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)),data_size);
	if(cpu.eflags.CF)
		cpu.eflags.CF = src>=dest;
	else
		cpu.eflags.CF = src>dest;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = dest - src - cpu.eflags.CF;

	set_CF_sbb(src, dest, data_size);
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	set_OF_sub(res,src,dest,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	uint64_t src0=sign_ext_64(src,data_size)&(0xFFFFFFFFFFFFFFFF>>(64-data_size));
	uint64_t dest0=sign_ext_64(dest,data_size)&(0xFFFFFFFFFFFFFFFF>>(64-data_size));
	uint64_t res = 0;
	res = dest0 * src0;
	uint64_t r=res;

	switch(data_size){
		case 8:r=r<<48>>56;break;
		case 16:r=r<<32>>48;break;
		default:r=r>>32;
	}
	if(r==0){
		cpu.eflags.CF=0;
		cpu.eflags.OF=0;
	}
	else{
		cpu.eflags.CF=1;
		cpu.eflags.OF=1;
	}
	return res & (0xFFFFFFFFFFFFFFFF >> (64-2*data_size));
} 

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	int64_t src0 = sign_ext_64(src,data_size);
	int64_t dest0 = sign_ext_64(dest,data_size);
	int64_t res = 0;
	res = src0 * dest0;
	return res;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	uint32_t res = 0;
	res = dest / src;

	return res;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	int32_t res = 0;
	res = dest / src;

	return res;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	uint32_t res = 0;
	res = dest % src;

	return res;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	int32_t res = 0;
	res = dest % src;

	return res;
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = src & dest;

	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = src ^ dest;

	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = 0;
	res = src | dest;

	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = dest;
	for(; src!=0; src--){
		cpu.eflags.CF = dest << (32 - data_size) >> 31;
		res = res * 2;
		dest = res;
	}

	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res & (0xFFFFFFFF >> (32 - data_size));
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t s=src;
	uint32_t res = dest;
	for(;src!=0;src--){
		cpu.eflags.CF = res % 2;
		res = res /2;
	}
	res=res&(0xFFFFFFFF >> (32 - data_size + s));

	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res;
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t s = src;
	uint32_t res = dest;
	for(;src!=0;src--){
		cpu.eflags.CF = res % 2;
		res = res/2;
	}
	dest = dest << (32 - data_size) >> 31;
	res=res&(0xFFFFFFFF>>(32 - data_size + s));
	if(dest)
		res=res|(0xFFFFFFFF>>(32-s)<<(data_size-s));
	
	set_PF(res);
	set_SF(res,data_size);
	set_ZF(res,data_size);
	return res;
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t res = dest;
	for(;src!=0;src--){
		cpu.eflags.CF=dest<<(32-data_size)>>31;
		res=res*2;
		dest=res;
	}

	set_PF(res);
	set_ZF(res,data_size);
	set_SF(res,data_size);
	return res & (0xFFFFFFFF >> (32-data_size));
}
