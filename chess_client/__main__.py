from .game import CmdController
import sys

controller = CmdController()

try:
    controller.cmdloop()
except KeyboardInterrupt:
    print("\nExiting program...")
    sys.exit(0)