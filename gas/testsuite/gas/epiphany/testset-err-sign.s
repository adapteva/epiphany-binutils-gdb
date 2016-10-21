; { dg-do assemble { target epiphany*-*-* } }

testset r52,[r32, r3] ; legal
testset r52,[r32,+r3] ; legal, backwards compatibility
testset r52,[r32,-r3] ; { dg-error "Error: negative direction not supported" }
