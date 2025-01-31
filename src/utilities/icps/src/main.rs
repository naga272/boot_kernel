#![no_std]  // Disabilita la libreria standard
#![no_main] // Disabilita il punto di ingresso standard di Rust


use core::panic::PanicInfo;
use regex::Regex;


#[no_mangle]  // Questo impedisce a Rust di modificare il nome della funzione
pub extern "C" fn icps_init() -> i32 {
    // Non possiamo usare println! perché richiede la libreria standard
    // Invece, possiamo implementare una funzione di stampa personalizzata
    // che utilizza il tuo sistema di output del kernel.
    // Ad esempio, potresti chiamare una funzione C che stampa a video.
    return 98;
}