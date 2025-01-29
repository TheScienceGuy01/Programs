def main():
    #Initialized boolean state conditions.
    isIdle = True
    isStartled = False
    isAlerted = False
    isBefriended = False
    isMad = False
    isDead = False

    #NPC Health
    npcHealth = 2

    #Initial statements
    print("You see an NPC in the distance and walk up to it.\n")
    print("It has 3 health points")

    #Until the NPC dies, the FSM will continue to run.
    while not isDead:

            #Initial state
            if isIdle:
                print("Choose an option")
                print("1. Sneak behind the NPC and say boo!")
                print("2. Walk in front of the person.\n")
                answer = input("Enter a path number: ")

                #Transitions available to current state
                if (answer == '1'):
                    isStartled = True
                    isIdle = False

                if (answer == '2'):
                    isAlerted = True
                    isIdle = False

            #State available after IDLE state 
            if isStartled:
                print("__________________________________________________________")
                print("        --------        ")
                print("     ---__    __---   ")
                print("    - _/        \_ -")
                print("   -   [ ]    [ ]   - ")
                print("   -                -")
                print("   -      ____      - ")
                print("    -    /    \    -")
                print("     ---  \__/  ---   ")
                print("        --------        ")
                print("NPC - OH! You scared me!")
                print("***The NPC has transitioned to the STARTLED state.***\n")

                isStartled = False
                isAlerted = True

            #State available after IDLE or STARTLED state
            if isAlerted:
                print("__________________________________________________________")
                print("        --------        ")
                print("     ---__    __---   ")
                print("    -  /        \  -")
                print("   -   [ ]    [ ]   - ")
                print("   -                -")
                print("   -      _____     - ")
                print("    -    |_____|   -")
                print("     ---         ---   ")
                print("        --------        ")
                print("NPC - Hello there.")
                print("***The NPC has transitioned to the ALERTED state.***\n")
                print("Choose an option")
                print("1. Say nothing.")
                print("2. Attack.")
                print("3. Give rose.\n")
                answer = input("Enter a path number: ")

                #Transitions available to current state
                if answer == '1':
                    isIdle = True
                    isAlerted = False
                if answer == '2':
                    print("ee")
                    isMad = True
                    isAlerted = False
                if answer == '3':
                    isAlerted = False
                    isBefriended = True

            #State available after ALERTED state
            if isBefriended:
                print("__________________________________________________________")
                print("        --------        ")
                print("     ---__    __---   ")
                print("    -  /        \  -")
                print("   -   [ ]    [ ]   - ")
                print("   -                -")
                print("   -      _____     - ")
                print("    -    \_____/   -")
                print("     ---         ---   ")
                print("        --------        ")
                print("NPC - Wow thank you for the rose!")
                print("***The NPC has transitioned to the BEFRIENDED state.***\n")
                print("Choose an option")
                print("1. Say nothing.")
                print("2. Attack")
                answer = input("Enter a path number: ")

                #Transitions available to current state
                if answer == '1':
                    print("You are now friends with the NPC.")
                if answer == '2':
                    isBefriended = False
                    isMad = True
                    print("NPC - Hey that hurts!\n")

            #State available after ALERTED or BEFRIENDED state
            if isMad:
                print("__________________________________________________________")
                print("        --------        ")
                print("     ---        ---   ")
                print("    -  \__    __/   -")
                print("   -   [ ]    [ ]   - ")
                print("   -                -")
                print("   -      _____     - ")
                print("    -    /_____\   -")
                print("     ---         ---   ")
                print("        --------        ")
                print("The NPC is now at",npcHealth, "health points\n")
                print("***The NPC has transitioned to the ATTACKED state.***\n")
                print("Choose an option")
                print("1. Say nothing.")
                print("2. Attack")

                #Transitions available to current state
                answer = input("Enter a path number: ")
                if npcHealth != 0 and answer == '2':
                    npcHealth -=1
                    isMad = True
                if npcHealth == 0:
                    isMad = False
                    isDead = True

            #State available after MAD state is active and the player chooses to attack the NPC unitl 0 health points
            if isDead:
                print("__________________________________________________________")
                print("        --------        ")
                print("     ---        ---   ")
                print("    -  ---    ---   -")
                print("   -   [X]    [X]   - ")
                print("   -                -")
                print("   -      _____     - ")
                print("    -    /     \   -")
                print("     ---         ---   ")
                print("        --------        ")
                print("You have killed the NPC!")

            #Checks if user has entered a valid input
            if (not (answer == '1' or answer == '2') and isAlerted == False) or (not (answer == '1' or answer == '2' or answer == '3') and isAlerted == True):
                print("\n----------***Please enter a valid number***----------\n")

#Called Main           
main()
