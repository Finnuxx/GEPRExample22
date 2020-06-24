# Example 2.2 - Exceptions, RAII, Operatoren, Friends

## Spielfeld
- 2 Dimensional
- 100x100
- enthält Ressourcen und Roboter

## Punkt
- x
- y
- definiert wo sich Ressourcen befinden

## Roboter
- können sich in alle Richtungen bewegen 
- befinden sich an einer Koordinate
- können Ressourcen abbauen
- können das gleiche Feld belegen

## Resourcen
- haben einen positiven Zahlenwert und Koordinate
- können abgebaut werden

## Startmechanik
- Roboter spawnen
- Ressourcen spawnen

## Bewegungsstrategie
- definiert Bewegung der Roboter

## Renderer
- alles was dargestellt wird braucht eine Renderfunktion

### Erklärungen:
 
Für die Implementation von Friends sah ich keine Notwendigkeit. Da auf keine 
geschützten oder privaten Bereiche einer anderen Klasse zugegriffen werden musste.

Da ich den Code von Beispiel 2.1 schon sehr ausführlich Dokumentiert habe, sind hier 
hauptsächlich Dokumentationen neuer Codebrocken vorhanden.