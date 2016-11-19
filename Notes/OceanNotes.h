-------------------------------------------------------------
Ocean
	Base
		0, 0.003, 0.01, 1.0
	base light
		0, 0.01933, 0.04, 1.0
	shallow 
		0.055, 0.10464, 0.15, 1.0
	base color lerp
		0.5
		2.0
		0.05
		0.05
	roughness
		0.005
		0.2
		1
		1
		30
		0.03
	scene color custom depth
		2000
	foam scale
		750	
		15
		20
		.45
		.8
		.075
		.3
		Ocean Ultra
-------------------------------------------------------------
Post Process Volume
	White Balance	
		Temp
			6000
	Color Grading
		Gamma
			1,1.02,1.04
	Scene Color
		Color grading intensity
			0.5
			lut_daytime
	bloom
		intensity 
			0.8
		threshold
			16
		dirt mask intensit
			20
		dirt mask
			T_ScreenDirt02_w
	auto exposure
		min bright
			0.7
		max bright
			1.5
	Lens Flares
		Intensity
			0.3
		tint
			0.78,0.922868,1.0
		bokehsize
			7.362831
		bokehshape
			defaultbokeh
		Tints
			1,.8,.4,.6
			.596908,1.035488,3.0,0.53
			.57479,.812371,1.2,
			.207,.371665,1.0,.39
			.090247,.229754,1,.35
			.090247,.229754,1,.35
			1,.8,.4,.22
			.34432,.606226,4.0,.56
	Deapth of field
		focal distance
			100
		region
			0
			150
			100000
		near blur siz
			4
			2
		sky distance 
			200000
	blendables underwater
			