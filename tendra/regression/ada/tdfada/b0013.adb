--  Purpose: check ranges operations.
--  Dependencies:: standard.ads

procedure B0013 is
   procedure Report (Status : Boolean);
   pragma Import (C, Report, "Report");

   type Int is range 10 .. 20;

   Zero   : constant Integer := Integer'Last - Integer'Last;
   One    : Integer := 1;
   Int_15 : constant Int := 15 + Int'Base'First - Int'Base'First;
   X_15   : Int := Int_15;
   Bool   : Boolean;
begin
   --  non-static expressions
   if One in 3 .. 5 then
      Report (False);
      return;
   end if;

   if One not in -3 .. 5 then
      Report (False);
      return;
   end if;

   if X_15 - 10 in Int'Range then
      Report (False);
      return;
   end if;

   if X_15 not in Int'Range then
      Report (False);
      return;
   end if;

   Bool := Zero in 3 .. Integer'Last;

   if Bool then
      Report (False);
      return;
   end if;

   --  static expressions
   if Zero in 3 .. 5 then
      Report (False);
      return;
   end if;

   if Zero not in -3 .. 5 then
      Report (False);
      return;
   end if;

   if 5 in Int'Range then
      Report (False);
      return;
   end if;

   if Int_15 - 10 in Int'Range then
      Report (False);
      return;
   end if;

   if Int_15 not in Int'Range then
      Report (False);
      return;
   end if;

   Report (True);
end B0013;
