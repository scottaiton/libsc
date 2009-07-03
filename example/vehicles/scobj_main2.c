
#include <sc.h>
#include <sc_object.h>
#include <car.h>

int
main (int argc, char ** argv)
{
  int                 i;
  float               wheelsize;
  sc_object_t        *object_klass;
  sc_object_t        *car_klass;
  sc_object_t        *o[3];
  sc_object_t        *c[1];

  sc_init (MPI_COMM_NULL, true, true, NULL, SC_LP_DEFAULT);

  object_klass = sc_object_klass_new ();

  o[0] = sc_object_new_from_klass (object_klass);
  o[1] = sc_object_new_from_klass (object_klass);

  car_klass = car_klass_new (object_klass);

  o[2] = c[0] = sc_object_new_from_klass (car_klass);

  SC_INFO ("Write klasses\n");
  sc_object_write (object_klass, stdout);
  sc_object_write (car_klass, stdout);

  SC_ASSERT (sc_object_is_type (c[0], car_type));
  wheelsize = car_wheelsize (c[0]);
  SC_INFOF ("Wheelsize %f\n", wheelsize);

  SC_INFO ("Write and destroy objects\n");
  for (i = 0; i < 3; ++i) {
    SC_ASSERT (sc_object_is_type (o[i], sc_object_type));
    sc_object_write (o[i], stdout);
    sc_object_unref (o[i]);
  }

  sc_object_unref (object_klass);
  sc_object_unref (car_klass);

  sc_finalize ();

  return 0;
}