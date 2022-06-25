#ifndef _IN_GAME_CREDITS_H
#define _IN_GAME_CREDITS_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

struct creditssprite {
	f32 unk00;
	f32 unk04;
	f32 unk08;
	f32 rotation;
	u8 unk10;
	u8 confignum;
	u8 unk12;
	u8 unk13;
	u8 unk14;
};

struct creditsbgtype {
	s16 unk00;
	s16 unk02;
	s16 unk04;
	s32 texturenum;
	f32 unk0c;
	f32 unk10;
};

struct creditsbglayer {
	s32 type;
	f32 rotatespeed;
	f32 unk08;
	u32 unk0c;
};

struct creditsdata {
	/*0x0000*/ u32 unk0000;
	/*0x0004*/ u32 unk0004;
	/*0x0008*/ u32 unk0008;
	/*0x000c*/ struct creditssprite sprites[500];
	/*0x2eec*/ u8 unk2eec;
	/*0x2eed*/ u8 unk2eed;
	/*0x2eee*/ u8 unk2eee;
	/*0x2eef*/ u8 unk2eef;
	/*0x2ef0*/ struct menu840 unk2ef0;
	/*0x34a8*/ u32 unk34a8;
	/*0x34ac*/ u32 unk34ac;
	/*0x34b0*/ u32 unk34b0;
	/*0x34b4*/ u32 unk34b4;
	/*0x34b8*/ u32 unk34b8;
	/*0x34bc*/ u32 unk34bc;
	/*0x34c0*/ u32 unk34c0;
	/*0x34c4*/ u32 unk34c4;
	/*0x34c8*/ u32 unk34c8;
	/*0x34cc*/ u32 unk34cc;
	/*0x34d0*/ u32 unk34d0;
	/*0x34d4*/ u32 unk34d4;
	/*0x34d8*/ u32 unk34d8;
	/*0x34dc*/ u32 unk34dc;
	/*0x34e0*/ u32 unk34e0;
	/*0x34e4*/ u32 unk34e4;
	/*0x34e8*/ u32 unk34e8;
	/*0x34ec*/ u32 unk34ec;
	/*0x34f0*/ u32 unk34f0;
	/*0x34f4*/ u32 unk34f4;
	/*0x34f8*/ u32 unk34f8;
	/*0x34fc*/ u32 unk34fc;
	/*0x3500*/ u32 unk3500;
	/*0x3504*/ u32 unk3504;
	/*0x3508*/ u32 unk3508;
	/*0x350c*/ u32 unk350c;
	/*0x3510*/ u32 unk3510;
	/*0x3514*/ u32 unk3514;
	/*0x3518*/ u32 unk3518;
	/*0x351c*/ u32 unk351c;
	/*0x3520*/ u32 unk3520;
	/*0x3524*/ u32 unk3524;
	/*0x3528*/ u32 unk3528;
	/*0x352c*/ u32 unk352c;
	/*0x3530*/ u32 unk3530;
	/*0x3534*/ u32 unk3534;
	/*0x3538*/ u32 unk3538;
	/*0x353c*/ u32 unk353c;
	/*0x3540*/ u32 unk3540;
	/*0x3544*/ u32 unk3544;
	/*0x3548*/ u32 unk3548;
	/*0x354c*/ u32 unk354c;
	/*0x3550*/ u32 unk3550;
	/*0x3554*/ u32 unk3554;
	/*0x3558*/ u32 unk3558;
	/*0x355c*/ u32 unk355c;
	/*0x3560*/ u32 unk3560;
	/*0x3564*/ u32 unk3564;
	/*0x3568*/ u32 unk3568;
	/*0x356c*/ u32 unk356c;
	/*0x3570*/ u32 unk3570;
	/*0x3574*/ u32 unk3574;
	/*0x3578*/ u32 unk3578;
	/*0x357c*/ u32 unk357c;
	/*0x3580*/ u32 unk3580;
	/*0x3584*/ u32 unk3584;
	/*0x3588*/ u32 unk3588;
	/*0x358c*/ u32 unk358c;
	/*0x3590*/ u32 unk3590;
	/*0x3594*/ u32 unk3594;
	/*0x3598*/ u32 unk3598;
	/*0x359c*/ u32 unk359c;
	/*0x35a0*/ u32 unk35a0;
	/*0x35a4*/ u32 unk35a4;
	/*0x35a8*/ u32 unk35a8;
	/*0x35ac*/ u32 unk35ac;
	/*0x35b0*/ u32 unk35b0;
	/*0x35b4*/ u32 unk35b4;
	/*0x35b8*/ u32 unk35b8;
	/*0x35bc*/ u32 unk35bc;
	/*0x35c0*/ u32 unk35c0;
	/*0x35c4*/ u32 unk35c4;
	/*0x35c8*/ u32 unk35c8;
	/*0x35cc*/ u32 unk35cc;
	/*0x35d0*/ u32 unk35d0;
	/*0x35d4*/ u32 unk35d4;
	/*0x35d8*/ u32 unk35d8;
	/*0x35dc*/ u32 unk35dc;
	/*0x35e0*/ u32 unk35e0;
	/*0x35e4*/ u32 unk35e4;
	/*0x35e8*/ u32 unk35e8;
	/*0x35ec*/ u32 unk35ec;
	/*0x35f0*/ u32 unk35f0;
	/*0x35f4*/ u32 unk35f4;
	/*0x35f8*/ u32 unk35f8;
	/*0x35fc*/ u32 unk35fc;
	/*0x3600*/ u32 unk3600;
	/*0x3604*/ u32 unk3604;
	/*0x3608*/ u32 unk3608;
	/*0x360c*/ u32 unk360c;
	/*0x3610*/ u32 unk3610;
	/*0x3614*/ u32 unk3614;
	/*0x3618*/ u32 unk3618;
	/*0x361c*/ u32 unk361c;
	/*0x3620*/ u32 unk3620;
	/*0x3624*/ u32 unk3624;
	/*0x3628*/ u32 unk3628;
	/*0x362c*/ u32 unk362c;
	/*0x3630*/ u32 unk3630;
	/*0x3634*/ u32 unk3634;
	/*0x3638*/ u32 unk3638;
	/*0x363c*/ u32 unk363c;
	/*0x3640*/ u32 unk3640;
	/*0x3644*/ u32 unk3644;
	/*0x3648*/ u32 unk3648;
	/*0x364c*/ u32 unk364c;
	/*0x3650*/ u32 unk3650;
	/*0x3654*/ u32 unk3654;
	/*0x3658*/ u32 unk3658;
	/*0x365c*/ u32 unk365c;
	/*0x3660*/ u32 unk3660;
	/*0x3664*/ u32 unk3664;
	/*0x3668*/ u32 unk3668;
	/*0x366c*/ u32 unk366c;
	/*0x3670*/ u32 unk3670;
	/*0x3674*/ u32 unk3674;
	/*0x3678*/ u32 unk3678;
	/*0x367c*/ u32 unk367c;
	/*0x3680*/ u32 unk3680;
	/*0x3684*/ u32 unk3684;
	/*0x3688*/ u32 unk3688;
	/*0x368c*/ u32 unk368c;
	/*0x3690*/ u32 unk3690;
	/*0x3694*/ u32 unk3694;
	/*0x3698*/ u32 unk3698;
	/*0x369c*/ u32 unk369c;
	/*0x36a0*/ u32 unk36a0;
	/*0x36a4*/ u32 unk36a4;
	/*0x36a8*/ u32 unk36a8;
	/*0x36ac*/ u32 unk36ac;
	/*0x36b0*/ u32 unk36b0;
	/*0x36b4*/ u32 unk36b4;
	/*0x36b8*/ u32 unk36b8;
	/*0x36bc*/ u32 unk36bc;
	/*0x36c0*/ u32 unk36c0;
	/*0x36c4*/ u32 unk36c4;
	/*0x36c8*/ u32 unk36c8;
	/*0x36cc*/ u32 unk36cc;
	/*0x36d0*/ u32 unk36d0;
	/*0x36d4*/ u32 unk36d4;
	/*0x36d8*/ u32 unk36d8;
	/*0x36dc*/ u32 unk36dc;
	/*0x36e0*/ u32 unk36e0;
	/*0x36e4*/ u32 unk36e4;
	/*0x36e8*/ u32 unk36e8;
	/*0x36ec*/ u32 unk36ec;
	/*0x36f0*/ u32 unk36f0;
	/*0x36f4*/ u32 unk36f4;
	/*0x36f8*/ u32 unk36f8;
	/*0x36fc*/ u32 unk36fc;
	/*0x3700*/ u32 unk3700;
	/*0x3704*/ u32 unk3704;
	/*0x3708*/ u32 unk3708;
	/*0x370c*/ u32 unk370c;
	/*0x3710*/ u32 unk3710;
	/*0x3714*/ u32 unk3714;
	/*0x3718*/ u32 unk3718;
	/*0x371c*/ u32 unk371c;
	/*0x3720*/ u32 unk3720;
	/*0x3724*/ u32 unk3724;
	/*0x3728*/ u32 unk3728;
	/*0x372c*/ u32 unk372c;
	/*0x3730*/ u32 unk3730;
	/*0x3734*/ u32 unk3734;
	/*0x3738*/ u32 unk3738;
	/*0x373c*/ u32 unk373c;
	/*0x3740*/ u32 unk3740;
	/*0x3744*/ u32 unk3744;
	/*0x3748*/ u32 unk3748;
	/*0x374c*/ u32 unk374c;
	/*0x3750*/ u32 unk3750;
	/*0x3754*/ u32 unk3754;
	/*0x3758*/ u32 unk3758;
	/*0x375c*/ u32 unk375c;
	/*0x3760*/ u32 unk3760;
	/*0x3764*/ u32 unk3764;
	/*0x3768*/ u32 unk3768;
	/*0x376c*/ u32 unk376c;
	/*0x3770*/ u32 unk3770;
	/*0x3774*/ u32 unk3774;
	/*0x3778*/ u32 unk3778;
	/*0x377c*/ u32 unk377c;
	/*0x3780*/ u32 unk3780;
	/*0x3784*/ u32 unk3784;
	/*0x3788*/ u32 unk3788;
	/*0x378c*/ u32 unk378c;
	/*0x3790*/ u32 unk3790;
	/*0x3794*/ u32 unk3794;
	/*0x3798*/ u32 unk3798;
	/*0x379c*/ u32 unk379c;
	/*0x37a0*/ u32 unk37a0;
	/*0x37a4*/ u32 unk37a4;
	/*0x37a8*/ u32 unk37a8;
	/*0x37ac*/ u32 unk37ac;
	/*0x37b0*/ u32 unk37b0;
	/*0x37b4*/ u32 unk37b4;
	/*0x37b8*/ u32 unk37b8;
	/*0x37bc*/ u32 unk37bc;
	/*0x37c0*/ u32 unk37c0;
	/*0x37c4*/ u32 unk37c4;
	/*0x37c8*/ u32 unk37c8;
	/*0x37cc*/ u32 unk37cc;
	/*0x37d0*/ u32 unk37d0;
	/*0x37d4*/ u32 unk37d4;
	/*0x37d8*/ u32 unk37d8;
	/*0x37dc*/ u32 unk37dc;
	/*0x37e0*/ u32 unk37e0;
	/*0x37e4*/ u32 unk37e4;
	/*0x37e8*/ u32 unk37e8;
	/*0x37ec*/ u32 unk37ec;
	/*0x37f0*/ u32 unk37f0;
	/*0x37f4*/ u32 unk37f4;
	/*0x37f8*/ u32 unk37f8;
	/*0x37fc*/ u32 unk37fc;
	/*0x3800*/ u32 unk3800;
	/*0x3804*/ u32 unk3804;
	/*0x3808*/ u32 unk3808;
	/*0x380c*/ u32 unk380c;
	/*0x3810*/ u32 unk3810;
	/*0x3814*/ u32 unk3814;
	/*0x3818*/ u32 unk3818;
	/*0x381c*/ u32 unk381c;
	/*0x3820*/ u32 unk3820;
	/*0x3824*/ u32 unk3824;
	/*0x3828*/ u32 unk3828;
	/*0x382c*/ u32 unk382c;
	/*0x3830*/ u32 unk3830;
	/*0x3834*/ u32 unk3834;
	/*0x3838*/ u32 unk3838;
	/*0x383c*/ u32 unk383c;
	/*0x3840*/ u32 unk3840;
	/*0x3844*/ u32 unk3844;
	/*0x3848*/ u32 unk3848;
	/*0x384c*/ u32 unk384c;
	/*0x3850*/ u32 unk3850;
	/*0x3854*/ u32 unk3854;
	/*0x3858*/ u32 unk3858;
	/*0x385c*/ u32 unk385c;
	/*0x3860*/ u32 unk3860;
	/*0x3864*/ u32 unk3864;
	/*0x3868*/ u32 unk3868;
	/*0x386c*/ u32 unk386c;
	/*0x3870*/ u32 unk3870;
	/*0x3874*/ u32 unk3874;
	/*0x3878*/ u32 unk3878;
	/*0x387c*/ u32 unk387c;
	/*0x3880*/ u32 unk3880;
	/*0x3884*/ u32 unk3884;
	/*0x3888*/ u32 unk3888;
	/*0x388c*/ u32 unk388c;
	/*0x3890*/ u32 unk3890;
	/*0x3894*/ u32 unk3894;
	/*0x3898*/ u32 unk3898;
	/*0x389c*/ u32 unk389c;
	/*0x38a0*/ u32 unk38a0;
	/*0x38a4*/ u32 unk38a4;
	/*0x38a8*/ u32 unk38a8;
	/*0x38ac*/ u32 unk38ac;
	/*0x38b0*/ u32 unk38b0;
	/*0x38b4*/ u32 unk38b4;
	/*0x38b8*/ u32 unk38b8;
	/*0x38bc*/ u32 unk38bc;
	/*0x38c0*/ u32 unk38c0;
	/*0x38c4*/ u32 unk38c4;
	/*0x38c8*/ u32 unk38c8;
	/*0x38cc*/ u32 unk38cc;
	/*0x38d0*/ u32 unk38d0;
	/*0x38d4*/ u32 unk38d4;
	/*0x38d8*/ u32 unk38d8;
	/*0x38dc*/ u32 unk38dc;
	/*0x38e0*/ u32 unk38e0;
	/*0x38e4*/ u32 unk38e4;
	/*0x38e8*/ u32 unk38e8;
	/*0x38ec*/ u32 unk38ec;
	/*0x38f0*/ u32 unk38f0;
	/*0x38f4*/ u32 unk38f4;
	/*0x38f8*/ u32 unk38f8;
	/*0x38fc*/ u32 unk38fc;
	/*0x3900*/ u32 unk3900;
	/*0x3904*/ u32 unk3904;
	/*0x3908*/ u32 unk3908;
	/*0x390c*/ u32 unk390c;
	/*0x3910*/ u32 unk3910;
	/*0x3914*/ u32 unk3914;
	/*0x3918*/ u32 unk3918;
	/*0x391c*/ u32 unk391c;
	/*0x3920*/ u32 unk3920;
	/*0x3924*/ u32 unk3924;
	/*0x3928*/ u32 unk3928;
	/*0x392c*/ u32 unk392c;
	/*0x3930*/ u32 unk3930;
	/*0x3934*/ u32 unk3934;
	/*0x3938*/ u32 unk3938;
	/*0x393c*/ u32 unk393c;
	/*0x3940*/ u32 unk3940;
	/*0x3944*/ u32 unk3944;
	/*0x3948*/ u32 unk3948;
	/*0x394c*/ u32 unk394c;
	/*0x3950*/ u32 unk3950;
	/*0x3954*/ u32 unk3954;
	/*0x3958*/ u32 unk3958;
	/*0x395c*/ u32 unk395c;
	/*0x3960*/ u32 unk3960;
	/*0x3964*/ u32 unk3964;
	/*0x3968*/ u32 unk3968;
	/*0x396c*/ u32 unk396c;
	/*0x3970*/ u32 unk3970;
	/*0x3974*/ u32 unk3974;
	/*0x3978*/ u32 unk3978;
	/*0x397c*/ u32 unk397c;
	/*0x3980*/ u32 unk3980;
	/*0x3984*/ u32 unk3984;
	/*0x3988*/ u32 unk3988;
	/*0x398c*/ u32 unk398c;
	/*0x3990*/ u32 unk3990;
	/*0x3994*/ u32 unk3994;
	/*0x3998*/ u32 unk3998;
	/*0x399c*/ u32 unk399c;
	/*0x39a0*/ u32 unk39a0;
	/*0x39a4*/ u32 unk39a4;
	/*0x39a8*/ u32 unk39a8;
	/*0x39ac*/ u32 unk39ac;
	/*0x39b0*/ u32 unk39b0;
	/*0x39b4*/ u32 unk39b4;
	/*0x39b8*/ u32 unk39b8;
	/*0x39bc*/ u32 unk39bc;
	/*0x39c0*/ u32 unk39c0;
	/*0x39c4*/ u32 unk39c4;
	/*0x39c8*/ u32 unk39c8;
	/*0x39cc*/ u32 unk39cc;
	/*0x39d0*/ u32 unk39d0;
	/*0x39d4*/ u32 unk39d4;
	/*0x39d8*/ u32 unk39d8;
	/*0x39dc*/ u32 unk39dc;
	/*0x39e0*/ u32 unk39e0;
	/*0x39e4*/ u32 unk39e4;
	/*0x39e8*/ u32 unk39e8;
	/*0x39ec*/ u32 unk39ec;
	/*0x39f0*/ u32 unk39f0;
	/*0x39f4*/ u32 unk39f4;
	/*0x39f8*/ u32 unk39f8;
	/*0x39fc*/ u32 unk39fc;
	/*0x3a00*/ u32 unk3a00;
	/*0x3a04*/ u32 unk3a04;
	/*0x3a08*/ u32 unk3a08;
	/*0x3a0c*/ u32 unk3a0c;
	/*0x3a10*/ u32 unk3a10;
	/*0x3a14*/ u32 unk3a14;
	/*0x3a18*/ u32 unk3a18;
	/*0x3a1c*/ u32 unk3a1c;
	/*0x3a20*/ u32 unk3a20;
	/*0x3a24*/ u32 unk3a24;
	/*0x3a28*/ u32 unk3a28;
	/*0x3a2c*/ u32 unk3a2c;
	/*0x3a30*/ u32 unk3a30;
	/*0x3a34*/ u32 unk3a34;
	/*0x3a38*/ u32 unk3a38;
	/*0x3a3c*/ u32 unk3a3c;
	/*0x3a40*/ u32 unk3a40;
	/*0x3a44*/ u32 unk3a44;
	/*0x3a48*/ u32 unk3a48;
	/*0x3a4c*/ u32 unk3a4c;
	/*0x3a50*/ u32 unk3a50;
	/*0x3a54*/ u32 unk3a54;
	/*0x3a58*/ u32 unk3a58;
	/*0x3a5c*/ u32 unk3a5c;
	/*0x3a60*/ u32 unk3a60;
	/*0x3a64*/ u32 unk3a64;
	/*0x3a68*/ u32 unk3a68;
	/*0x3a6c*/ u32 unk3a6c;
	/*0x3a70*/ u32 unk3a70;
	/*0x3a74*/ u32 unk3a74;
	/*0x3a78*/ u32 unk3a78;
	/*0x3a7c*/ u32 unk3a7c;
	/*0x3a80*/ u32 unk3a80;
	/*0x3a84*/ u32 unk3a84;
	/*0x3a88*/ u32 unk3a88;
	/*0x3a8c*/ u32 unk3a8c;
	/*0x3a90*/ u32 unk3a90;
	/*0x3a94*/ u32 unk3a94;
	/*0x3a98*/ u32 unk3a98;
	/*0x3a9c*/ u32 unk3a9c;
	/*0x3aa0*/ u32 unk3aa0;
	/*0x3aa4*/ u32 unk3aa4;
	/*0x3aa8*/ u32 unk3aa8;
	/*0x3aac*/ u32 unk3aac;
	/*0x3ab0*/ u32 unk3ab0;
	/*0x3ab4*/ u32 unk3ab4;
	/*0x3ab8*/ u32 unk3ab8;
	/*0x3abc*/ u32 unk3abc;
	/*0x3ac0*/ u32 unk3ac0;
	/*0x3ac4*/ u32 unk3ac4;
	/*0x3ac8*/ u32 unk3ac8;
	/*0x3acc*/ u32 unk3acc;
	/*0x3ad0*/ u32 unk3ad0;
	/*0x3ad4*/ u32 unk3ad4;
	/*0x3ad8*/ u32 unk3ad8;
	/*0x3adc*/ u32 unk3adc;
	/*0x3ae0*/ u32 unk3ae0;
	/*0x3ae4*/ u32 unk3ae4;
	/*0x3ae8*/ u32 unk3ae8;
	/*0x3aec*/ u32 unk3aec;
	/*0x3af0*/ u32 unk3af0;
	/*0x3af4*/ u32 unk3af4;
	/*0x3af8*/ u32 unk3af8;
	/*0x3afc*/ u32 unk3afc;
	/*0x3b00*/ u32 unk3b00;
	/*0x3b04*/ u32 unk3b04;
	/*0x3b08*/ u32 unk3b08;
	/*0x3b0c*/ u32 unk3b0c;
	/*0x3b10*/ u32 unk3b10;
	/*0x3b14*/ u32 unk3b14;
	/*0x3b18*/ u32 unk3b18;
	/*0x3b1c*/ u32 unk3b1c;
	/*0x3b20*/ u32 unk3b20;
	/*0x3b24*/ u32 unk3b24;
	/*0x3b28*/ u32 unk3b28;
	/*0x3b2c*/ u32 unk3b2c;
	/*0x3b30*/ u32 unk3b30;
	/*0x3b34*/ u32 unk3b34;
	/*0x3b38*/ u32 unk3b38;
	/*0x3b3c*/ u32 unk3b3c;
	/*0x3b40*/ u32 unk3b40;
	/*0x3b44*/ u32 unk3b44;
	/*0x3b48*/ u32 unk3b48;
	/*0x3b4c*/ u32 unk3b4c;
	/*0x3b50*/ u32 unk3b50;
	/*0x3b54*/ u32 unk3b54;
	/*0x3b58*/ u32 unk3b58;
	/*0x3b5c*/ u32 unk3b5c;
	/*0x3b60*/ u32 unk3b60;
	/*0x3b64*/ u32 unk3b64;
	/*0x3b68*/ u32 unk3b68;
	/*0x3b6c*/ u32 unk3b6c;
	/*0x3b70*/ u32 unk3b70;
	/*0x3b74*/ u32 unk3b74;
	/*0x3b78*/ u32 unk3b78;
	/*0x3b7c*/ u32 unk3b7c;
	/*0x3b80*/ u32 unk3b80;
	/*0x3b84*/ u32 unk3b84;
	/*0x3b88*/ u32 unk3b88;
	/*0x3b8c*/ u32 unk3b8c;
	/*0x3b90*/ u32 unk3b90;
	/*0x3b94*/ u32 unk3b94;
	/*0x3b98*/ u32 unk3b98;
	/*0x3b9c*/ u32 unk3b9c;
	/*0x3ba0*/ u32 unk3ba0;
	/*0x3ba4*/ u32 unk3ba4;
	/*0x3ba8*/ u32 unk3ba8;
	/*0x3bac*/ u32 unk3bac;
	/*0x3bb0*/ u32 unk3bb0;
	/*0x3bb4*/ u32 unk3bb4;
	/*0x3bb8*/ u32 unk3bb8;
	/*0x3bbc*/ u32 unk3bbc;
	/*0x3bc0*/ u32 unk3bc0;
	/*0x3bc4*/ u32 unk3bc4;
	/*0x3bc8*/ u32 unk3bc8;
	/*0x3bcc*/ u32 unk3bcc;
	/*0x3bd0*/ u32 unk3bd0;
	/*0x3bd4*/ u32 unk3bd4;
	/*0x3bd8*/ u32 unk3bd8;
	/*0x3bdc*/ u32 unk3bdc;
	/*0x3be0*/ u32 unk3be0;
	/*0x3be4*/ u32 unk3be4;
	/*0x3be8*/ u32 unk3be8;
	/*0x3bec*/ u32 unk3bec;
	/*0x3bf0*/ u32 unk3bf0;
	/*0x3bf4*/ u32 unk3bf4;
	/*0x3bf8*/ u32 unk3bf8;
	/*0x3bfc*/ u32 unk3bfc;
	/*0x3c00*/ u32 unk3c00;
	/*0x3c04*/ u32 unk3c04;
	/*0x3c08*/ u32 unk3c08;
	/*0x3c0c*/ u32 unk3c0c;
	/*0x3c10*/ u32 unk3c10;
	/*0x3c14*/ u32 unk3c14;
	/*0x3c18*/ u32 unk3c18;
	/*0x3c1c*/ u32 unk3c1c;
	/*0x3c20*/ u32 unk3c20;
	/*0x3c24*/ u32 unk3c24;
	/*0x3c28*/ u32 unk3c28;
	/*0x3c2c*/ u32 unk3c2c;
	/*0x3c30*/ u32 unk3c30;
	/*0x3c34*/ u32 unk3c34;
	/*0x3c38*/ u32 unk3c38;
	/*0x3c3c*/ u32 unk3c3c;
	/*0x3c40*/ u32 unk3c40;
	/*0x3c44*/ u32 unk3c44;
	/*0x3c48*/ u32 unk3c48;
	/*0x3c4c*/ u32 unk3c4c;
	/*0x3c50*/ u32 unk3c50;
	/*0x3c54*/ u32 unk3c54;
	/*0x3c58*/ u32 unk3c58;
	/*0x3c5c*/ u32 unk3c5c;
	/*0x3c60*/ u32 unk3c60;
	/*0x3c64*/ u32 unk3c64;
	/*0x3c68*/ u32 unk3c68;
	/*0x3c6c*/ u32 unk3c6c;
	/*0x3c70*/ u32 unk3c70;
	/*0x3c74*/ u32 unk3c74;
	/*0x3c78*/ u32 unk3c78;
	/*0x3c7c*/ u32 unk3c7c;
	/*0x3c80*/ u32 unk3c80;
	/*0x3c84*/ u32 unk3c84;
	/*0x3c88*/ u32 unk3c88;
	/*0x3c8c*/ u32 unk3c8c;
	/*0x3c90*/ u32 unk3c90;
	/*0x3c94*/ u32 unk3c94;
	/*0x3c98*/ u32 unk3c98;
	/*0x3c9c*/ u32 unk3c9c;
	/*0x3ca0*/ u32 unk3ca0;
	/*0x3ca4*/ u32 unk3ca4;
	/*0x3ca8*/ u32 unk3ca8;
	/*0x3cac*/ u32 unk3cac;
	/*0x3cb0*/ u32 unk3cb0;
	/*0x3cb4*/ u32 unk3cb4;
	/*0x3cb8*/ u32 unk3cb8;
	/*0x3cbc*/ u32 unk3cbc;
	/*0x3cc0*/ u32 unk3cc0;
	/*0x3cc4*/ u32 unk3cc4;
	/*0x3cc8*/ u32 unk3cc8;
	/*0x3ccc*/ u32 unk3ccc;
	/*0x3cd0*/ u32 unk3cd0;
	/*0x3cd4*/ u32 unk3cd4;
	/*0x3cd8*/ u32 unk3cd8;
	/*0x3cdc*/ u32 unk3cdc;
	/*0x3ce0*/ u32 unk3ce0;
	/*0x3ce4*/ u32 unk3ce4;
	/*0x3ce8*/ u32 unk3ce8;
	/*0x3cec*/ u32 unk3cec;
	/*0x3cf0*/ u32 unk3cf0;
	/*0x3cf4*/ u32 unk3cf4;
	/*0x3cf8*/ u32 unk3cf8;
	/*0x3cfc*/ u32 unk3cfc;
	/*0x3d00*/ u32 unk3d00;
	/*0x3d04*/ u32 unk3d04;
	/*0x3d08*/ u32 unk3d08;
	/*0x3d0c*/ u32 unk3d0c;
	/*0x3d10*/ u32 unk3d10;
	/*0x3d14*/ u32 unk3d14;
	/*0x3d18*/ u32 unk3d18;
	/*0x3d1c*/ u32 unk3d1c;
	/*0x3d20*/ u32 unk3d20;
	/*0x3d24*/ u32 unk3d24;
	/*0x3d28*/ u32 unk3d28;
	/*0x3d2c*/ u32 unk3d2c;
	/*0x3d30*/ u32 unk3d30;
	/*0x3d34*/ u32 unk3d34;
	/*0x3d38*/ u32 unk3d38;
	/*0x3d3c*/ u32 unk3d3c;
	/*0x3d40*/ u32 unk3d40;
	/*0x3d44*/ u32 unk3d44;
	/*0x3d48*/ u32 unk3d48;
	/*0x3d4c*/ u32 unk3d4c;
	/*0x3d50*/ u32 unk3d50;
	/*0x3d54*/ u32 unk3d54;
	/*0x3d58*/ u32 unk3d58;
	/*0x3d5c*/ u32 unk3d5c;
	/*0x3d60*/ u32 unk3d60;
	/*0x3d64*/ u32 unk3d64;
	/*0x3d68*/ u32 unk3d68;
	/*0x3d6c*/ u32 unk3d6c;
	/*0x3d70*/ u32 unk3d70;
	/*0x3d74*/ u32 unk3d74;
	/*0x3d78*/ u32 unk3d78;
	/*0x3d7c*/ u32 unk3d7c;
	/*0x3d80*/ u32 unk3d80;
	/*0x3d84*/ u32 unk3d84;
	/*0x3d88*/ u32 unk3d88;
	/*0x3d8c*/ u32 unk3d8c;
	/*0x3d90*/ u32 unk3d90;
	/*0x3d94*/ u32 unk3d94;
	/*0x3d98*/ u32 unk3d98;
	/*0x3d9c*/ u32 unk3d9c;
	/*0x3da0*/ u32 unk3da0;
	/*0x3da4*/ u32 unk3da4;
	/*0x3da8*/ u32 unk3da8;
	/*0x3dac*/ u32 unk3dac;
	/*0x3db0*/ u32 unk3db0;
	/*0x3db4*/ u32 unk3db4;
	/*0x3db8*/ u32 unk3db8;
	/*0x3dbc*/ u32 unk3dbc;
	/*0x3dc0*/ u32 unk3dc0;
	/*0x3dc4*/ u32 unk3dc4;
	/*0x3dc8*/ u32 unk3dc8;
	/*0x3dcc*/ u32 unk3dcc;
	/*0x3dd0*/ u32 unk3dd0;
	/*0x3dd4*/ u32 unk3dd4;
	/*0x3dd8*/ u32 unk3dd8;
	/*0x3ddc*/ u32 unk3ddc;
	/*0x3de0*/ u32 unk3de0;
	/*0x3de4*/ u32 unk3de4;
	/*0x3de8*/ u32 unk3de8;
	/*0x3dec*/ u32 unk3dec;
	/*0x3df0*/ u32 unk3df0;
	/*0x3df4*/ u32 unk3df4;
	/*0x3df8*/ u32 unk3df8;
	/*0x3dfc*/ u32 unk3dfc;
	/*0x3e00*/ u32 unk3e00;
	/*0x3e04*/ u32 unk3e04;
	/*0x3e08*/ u32 unk3e08;
	/*0x3e0c*/ u32 unk3e0c;
	/*0x3e10*/ u32 unk3e10;
	/*0x3e14*/ u32 unk3e14;
	/*0x3e18*/ u32 unk3e18;
	/*0x3e1c*/ u32 unk3e1c;
	/*0x3e20*/ u32 unk3e20;
	/*0x3e24*/ u32 unk3e24;
	/*0x3e28*/ u32 unk3e28;
	/*0x3e2c*/ u32 unk3e2c;
	/*0x3e30*/ u32 unk3e30;
	/*0x3e34*/ u32 unk3e34;
	/*0x3e38*/ u32 unk3e38;
	/*0x3e3c*/ u32 unk3e3c;
	/*0x3e40*/ u32 unk3e40;
	/*0x3e44*/ u32 unk3e44;
	/*0x3e48*/ u32 unk3e48;
	/*0x3e4c*/ u32 unk3e4c;
	/*0x3e50*/ u32 unk3e50;
	/*0x3e54*/ u32 unk3e54;
	/*0x3e58*/ u32 unk3e58;
	/*0x3e5c*/ u32 unk3e5c;
	/*0x3e60*/ u32 unk3e60;
	/*0x3e64*/ u32 unk3e64;
	/*0x3e68*/ u32 unk3e68;
	/*0x3e6c*/ u32 unk3e6c;
	/*0x3e70*/ u32 unk3e70;
	/*0x3e74*/ u32 unk3e74;
	/*0x3e78*/ u32 unk3e78;
	/*0x3e7c*/ u32 unk3e7c;
	/*0x3e80*/ u32 unk3e80;
	/*0x3e84*/ u32 unk3e84;
	/*0x3e88*/ u32 unk3e88;
	/*0x3e8c*/ u32 unk3e8c;
	/*0x3e90*/ u32 unk3e90;
	/*0x3e94*/ u32 unk3e94;
	/*0x3e98*/ u32 unk3e98;
	/*0x3e9c*/ u32 unk3e9c;
	/*0x3ea0*/ u32 unk3ea0;
	/*0x3ea4*/ u32 unk3ea4;
	/*0x3ea8*/ u32 unk3ea8;
	/*0x3eac*/ u32 unk3eac;
	/*0x3eb0*/ u32 unk3eb0;
	/*0x3eb4*/ u32 unk3eb4;
	/*0x3eb8*/ u32 unk3eb8;
	/*0x3ebc*/ u32 unk3ebc;
	/*0x3ec0*/ u32 unk3ec0;
	/*0x3ec4*/ u32 unk3ec4;
	/*0x3ec8*/ u32 unk3ec8;
	/*0x3ecc*/ u32 unk3ecc;
	/*0x3ed0*/ u32 unk3ed0;
	/*0x3ed4*/ u32 unk3ed4;
	/*0x3ed8*/ u32 unk3ed8;
	/*0x3edc*/ u32 unk3edc;
	/*0x3ee0*/ u32 unk3ee0;
	/*0x3ee4*/ u32 unk3ee4;
	/*0x3ee8*/ u32 unk3ee8;
	/*0x3eec*/ u32 unk3eec;
	/*0x3ef0*/ u32 unk3ef0;
	/*0x3ef4*/ u32 unk3ef4;
	/*0x3ef8*/ u32 unk3ef8;
	/*0x3efc*/ u32 unk3efc;
	/*0x3f00*/ u32 unk3f00;
	/*0x3f04*/ u32 unk3f04;
	/*0x3f08*/ u32 unk3f08;
	/*0x3f0c*/ u32 unk3f0c;
	/*0x3f10*/ u32 unk3f10;
	/*0x3f14*/ u32 unk3f14;
	/*0x3f18*/ u32 unk3f18;
	/*0x3f1c*/ u32 unk3f1c;
	/*0x3f20*/ u32 unk3f20;
	/*0x3f24*/ u32 unk3f24;
	/*0x3f28*/ u32 unk3f28;
	/*0x3f2c*/ u32 unk3f2c;
	/*0x3f30*/ u32 unk3f30;
	/*0x3f34*/ u32 unk3f34;
	/*0x3f38*/ u32 unk3f38;
	/*0x3f3c*/ u32 unk3f3c;
	/*0x3f40*/ u32 unk3f40;
	/*0x3f44*/ u32 unk3f44;
	/*0x3f48*/ u32 unk3f48;
	/*0x3f4c*/ u32 unk3f4c;
	/*0x3f50*/ u32 unk3f50;
	/*0x3f54*/ u32 unk3f54;
	/*0x3f58*/ u32 unk3f58;
	/*0x3f5c*/ u32 unk3f5c;
	/*0x3f60*/ u32 unk3f60;
	/*0x3f64*/ u32 unk3f64;
	/*0x3f68*/ u32 unk3f68;
	/*0x3f6c*/ u32 unk3f6c;
	/*0x3f70*/ u32 unk3f70;
	/*0x3f74*/ u32 unk3f74;
	/*0x3f78*/ u32 unk3f78;
	/*0x3f7c*/ u32 unk3f7c;
	/*0x3f80*/ u32 unk3f80;
	/*0x3f84*/ u32 unk3f84;
	/*0x3f88*/ u32 unk3f88;
	/*0x3f8c*/ u32 unk3f8c;
	/*0x3f90*/ u32 unk3f90;
	/*0x3f94*/ u32 unk3f94;
	/*0x3f98*/ u32 unk3f98;
	/*0x3f9c*/ u32 unk3f9c;
	/*0x3fa0*/ u32 unk3fa0;
	/*0x3fa4*/ u32 unk3fa4;
	/*0x3fa8*/ u32 unk3fa8;
	/*0x3fac*/ u32 unk3fac;
	/*0x3fb0*/ u32 unk3fb0;
	/*0x3fb4*/ u32 unk3fb4;
	/*0x3fb8*/ u32 unk3fb8;
	/*0x3fbc*/ u32 unk3fbc;
	/*0x3fc0*/ u32 unk3fc0;
	/*0x3fc4*/ u32 unk3fc4;
	/*0x3fc8*/ u32 unk3fc8;
	/*0x3fcc*/ u32 unk3fcc;
	/*0x3fd0*/ u32 unk3fd0;
	/*0x3fd4*/ u32 unk3fd4;
	/*0x3fd8*/ u32 unk3fd8;
	/*0x3fdc*/ u32 unk3fdc;
	/*0x3fe0*/ u32 unk3fe0;
	/*0x3fe4*/ u32 unk3fe4;
	/*0x3fe8*/ u32 unk3fe8;
	/*0x3fec*/ u32 unk3fec;
	/*0x3ff0*/ u32 unk3ff0;
	/*0x3ff4*/ u32 unk3ff4;
	/*0x3ff8*/ u32 unk3ff8;
	/*0x3ffc*/ u32 unk3ffc;
	/*0x4000*/ u32 unk4000;
	/*0x4004*/ u32 unk4004;
	/*0x4008*/ u32 unk4008;
	/*0x400c*/ u32 unk400c;
	/*0x4010*/ u32 unk4010;
	/*0x4014*/ u32 unk4014;
	/*0x4018*/ u32 unk4018;
	/*0x401c*/ u32 unk401c;
	/*0x4020*/ u32 unk4020;
	/*0x4024*/ u32 unk4024;
	/*0x4028*/ u32 unk4028;
	/*0x402c*/ u32 unk402c;
	/*0x4030*/ u32 unk4030;
	/*0x4034*/ u32 unk4034;
	/*0x4038*/ u32 unk4038;
	/*0x403c*/ u32 unk403c;
	/*0x4040*/ u32 unk4040;
	/*0x4044*/ u32 unk4044;
	/*0x4048*/ u32 unk4048;
	/*0x404c*/ u32 unk404c;
	/*0x4050*/ u32 unk4050;
	/*0x4054*/ u32 unk4054;
	/*0x4058*/ u32 unk4058;
	/*0x405c*/ u32 unk405c;
	/*0x4060*/ u32 unk4060;
	/*0x4064*/ u32 unk4064;
	/*0x4068*/ u32 unk4068;
	/*0x406c*/ u32 unk406c;
	/*0x4070*/ u32 unk4070;
	/*0x4074*/ u32 unk4074;
	/*0x4078*/ u32 unk4078;
	/*0x407c*/ u32 unk407c;
	/*0x4080*/ u32 unk4080;
	/*0x4084*/ u32 unk4084;
	/*0x4088*/ u32 unk4088;
	/*0x408c*/ u32 unk408c;
	/*0x4090*/ u32 unk4090;
	/*0x4094*/ u32 unk4094;
	/*0x4098*/ u32 unk4098;
	/*0x409c*/ u32 unk409c;
	/*0x40a0*/ u32 unk40a0;
	/*0x40a4*/ u32 unk40a4;
	/*0x40a8*/ u32 unk40a8;
	/*0x40ac*/ u32 unk40ac;
	/*0x40b0*/ u32 unk40b0;
	/*0x40b4*/ u32 unk40b4;
	/*0x40b8*/ u32 unk40b8;
	/*0x40bc*/ u32 unk40bc;
	/*0x40c0*/ u32 unk40c0;
	/*0x40c4*/ u32 unk40c4;
	/*0x40c8*/ u32 unk40c8;
	/*0x40cc*/ u32 unk40cc;
	/*0x40d0*/ u32 unk40d0;
	/*0x40d4*/ u32 unk40d4;
	/*0x40d8*/ u32 unk40d8;
	/*0x40dc*/ u32 unk40dc;
	/*0x40e0*/ u32 unk40e0;
	/*0x40e4*/ u32 unk40e4;
	/*0x40e8*/ u32 unk40e8;
	/*0x40ec*/ u32 unk40ec;
	/*0x40f0*/ u32 unk40f0;
	/*0x40f4*/ u32 unk40f4;
	/*0x40f8*/ u32 unk40f8;
	/*0x40fc*/ u32 unk40fc;
	/*0x4100*/ u32 unk4100;
	/*0x4104*/ u32 unk4104;
	/*0x4108*/ u32 unk4108;
	/*0x410c*/ u32 unk410c;
	/*0x4110*/ u32 unk4110;
	/*0x4114*/ u32 unk4114;
	/*0x4118*/ u32 unk4118;
	/*0x411c*/ u32 unk411c;
	/*0x4120*/ u32 unk4120;
	/*0x4124*/ u32 unk4124;
	/*0x4128*/ u32 unk4128;
	/*0x412c*/ u32 unk412c;
	/*0x4130*/ u32 unk4130;
	/*0x4134*/ u32 unk4134;
	/*0x4138*/ u32 unk4138;
	/*0x413c*/ u32 unk413c;
	/*0x4140*/ u32 unk4140;
	/*0x4144*/ u32 unk4144;
	/*0x4148*/ u32 unk4148;
	/*0x414c*/ u32 unk414c;
	/*0x4150*/ u32 unk4150;

	/**
	 * Credit indexes 1 through 16 are randomised. coreteammap stores the chosen
	 * order. The index is the apparent credit index and the value is the real
	 * credit index that it maps to.
	 */
	/*0x4154*/ u32 coreteammap[17];

	/**
	 * creditnum is the credit index of the first credit being displayed on the
	 * current slide. It's usually a title.
	 *
	 * However, if creditnum is between 1 and 16 then this value gets mapped
	 * through the coreteammap, so its value won't actually correspond with the
	 * credit being displayed.
	 */
	/*0x4198*/ s32 creditnum;

	/*0x419c*/ u8 numthisslide;
	/*0x41a0*/ f32 slideage; // age in seconds
	/*0x41a4*/ f32 slidelifetime; // in seconds
	/*0x41a8*/ u8 unk41a8[8];
	/*0x41b0*/ s8 unk41b0[2];
	/*0x41b4*/ struct creditsbglayer bglayers[4];
	/*0x41f4*/ u8 slidesenabled;
	/*0x41f5*/ s8 unk41f5;
	/*0x41f6*/ s8 unk41f6;
	/*0x41f8*/ f32 unk41f8;
	/*0x41fc*/ u8 unk41fc;
	/*0x41fd*/ u8 unk41fd;
	/*0x41fe*/ u8 unk41fe;
	/*0x41ff*/ u8 unk41ff;
	/*0x4200*/ u8 unk4200;
	/*0x4204*/ u32 unk4204; // time 60
	/*0x4208*/ u8 unk4208;
	/*0x420c*/ u32 unk420c;
	/*0x4210*/ u32 unk4210;
	/*0x4214*/ u32 unk4214;
	/*0x4218*/ u32 unk4218;
	/*0x421c*/ u32 unk421c;
	/*0x4220*/ u32 unk4220;
	/*0x4224*/ u32 unk4224;
	/*0x4228*/ u32 unk4228;
	/*0x422c*/ u32 unk422c;
	/*0x4230*/ u32 unk4230;
	/*0x4234*/ u32 unk4234;
	/*0x4238*/ u32 unk4238;
	/*0x423c*/ u32 unk423c;
};

void func0f137430(struct gfxvtx *vertices, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void creditsInitVertices(struct gfxvtx *vertices, s32 z);
void func0f137874(struct gfxvtx *vertices, u32 *colours, s32 arg2, s32 alpha, s32 arg4);
Gfx *creditsRenderBackgroundLayer(Gfx *gdl, u8 type, u8 layernum, f32 arg3, u32 alpha, s32 arg5);
void creditsCopyBackgroundLayer(s32 srcindex, s32 dstindex, bool move);
Gfx *creditsRenderBackground(Gfx *gdl);
f32 func0f1382e0(f32 range);
void creditsCreatePendingBgLayers(u32 mask);
Gfx *creditsClearFramebuffer(Gfx *gdl, u32 colour);
void creditsResetSprites(void);
void func0f13899c(void);
void creditsGetSpritePos(struct coord *pos, struct creditssprite *sprite, s32 spritenum);
Gfx *creditsRenderSprites(Gfx *gdl);
u32 func0f1399d0(void);
u32 func0f139d9c(void);
void creditsResetSlides(void);
struct credit *creditGetByRow(s32 row);
void creditsTickSlide(void);
Gfx *func0f13a3ec(Gfx *gdl);
void credits0f13ae04(Mtxf *mtx);
void creditsTick(void);
Gfx *creditsRender(Gfx *gdl);
void creditsReset(void);
void creditsRequestAltTitle(void);

#endif
