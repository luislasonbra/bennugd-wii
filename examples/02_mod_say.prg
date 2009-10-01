Process main()
Private
  int i=0, maxi=100;

Begin
  // Test for the functions inside mod_say
  for(i=0;i<maxi;i++)
    say("say'ing "+i);
  end;

  for(i=0;i<maxi;i++)
    say_fast("say_fast'ing "+i);
  end;

  return 0;
End;
