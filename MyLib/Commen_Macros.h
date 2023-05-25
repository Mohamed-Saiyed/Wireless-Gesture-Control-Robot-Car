#ifndef COMMEN_MACROS_H
#define COMMEN_MACROS_H

#define SET_BIT(VAR,BITNO)        VAR |= (1<< (BITNO))
#define CLEAR_BIT(VAR,BITNO)      VAR &=~(1<< (BITNO))
#define TOGGLE_BIT(VAR,BITNO)     VAR ^= (1<< (BITNO))
#define BIT_IS_CLEAR(VAR,BITNO)   (!VAR &(1<<BITNO))
#define BIT_IS_SET(VAR,BITNO)     (VAR &(1<<BITNO))


#endif /*COMMEN_MACROS_H*/