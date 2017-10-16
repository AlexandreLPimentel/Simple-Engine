/*#pragma once
#define CATCH_CONFIG_MAIN
#include "test/api/catch.hpp"
#include "vector.h"
#include "matrix.h"

/*************************vec2 tests*************************_

SCENARIO("vec2 can be instantiated", "[vec2]") {
	GIVEN("a default vec2 with 0,0 coordinates") {
		vec2 v = vec2();
		REQUIRE(v.getX() == 0.0f);
		REQUIRE(v.getY() == 0.0f);
		WHEN("the coordinates are changed") {
			v.setX(2.0f);
			v.setY(3.0f);
			THEN("they must be changed") {
				REQUIRE(v.getX() == 2.0f);
				REQUIRE(v.getY() == 3.0f);
			}
		}
	}
	GIVEN("a vec2 created with the float constructor") {
		vec2 v = vec2(1.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 1.0f);
	}
	GIVEN("a vec2 created with the coordinate specification constructor") {
		vec2 v = vec2(1.0f, 2.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 2.0f);
	}
	GIVEN("a vec2 created in any way") {
		vec2 v = vec2(1.0f, 2.0f);
		WHEN("we create a copy of this vec2") {
			vec2 v2 = vec2(v);
			THEN("the coordinates must be the same") {
				REQUIRE(v.getX() == 1.0f);
				REQUIRE(v.getY() == 2.0f);
			}
		}
	}
}

SCENARIO("vec2 can use operators", "[vec2]") {
	GIVEN("two vec2 created in any way") {
		vec2 u = vec2(4.0f, 2.0f);
		vec2 v = vec2(3.0f, 3.0f);
		WHEN("add one to the other") {
			vec2 w = u + v;
			THEN("the coordinates of the resulting vec2 must be correct") {
				REQUIRE(w.getX() == 7.0f);
				REQUIRE(w.getY() == 5.0f);
			}
			WHEN("we reverse the order") {
				vec2 z = v + u;
				THEN("the addition must be commutative") {
					REQUIRE(w.getX() == 7.0f);
					REQUIRE(w.getY() == 5.0f);
				}
			}
		}
		WHEN("subtract one to the other") {
			vec2 w = u - v;
			THEN("the coordinates of the resulting vec2 must be correct") {
				REQUIRE(w.getX() == 1.0f);
				REQUIRE(w.getY() == -1.0f);
			}
			WHEN("we reverse the order") {
				vec2 z = v - u;
				THEN("the subtraction must not be commutative") {
					REQUIRE(z.getX() == -1.0f);
					REQUIRE(z.getY() == 1.0f);
				}
			}
		}
		WHEN("multiply one of them by a scalar") {
			vec2 w = u * 3.0f;
			THEN("the coordinates of the resulting vec2 must be correct") {
				REQUIRE(w.getX() == 12.0f);
				REQUIRE(w.getY() == 6.0f);
			}
			WHEN("we reverse the order") {
				vec2 z = 3.0f * u;
				THEN("the multiplication must be commutative") {
					REQUIRE(w.getX() == 12.0f);
					REQUIRE(w.getY() == 6.0f);
				}
			}
		}
		WHEN("divide one of them by a scalar") {
			vec2 w = u / 10.0f;
			THEN("the coordinates of the resulting vec2 must be correct") {
				REQUIRE(w.getX() == 0.4f);
				REQUIRE(w.getY() == 0.2f);
			}
		}
	}
	GIVEN("A vec2 created in any way") {
		vec2 u = vec2(3.0f, 2.0f);
		WHEN("assign another vec2 to it") {
			u = vec2(0.0f, 2.0f);
			THEN("the coordinates of the first vec2 must be changed") {
				REQUIRE(u.getX() == 0.0f);
				REQUIRE(u.getY() == 2.0f);
			}
		}
		WHEN("add-assign another vec2 to it") {
			u += vec2(0.0f, 2.0f);
			THEN("the coordinates of the first vec2 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 4.0f);
			}
		}
		WHEN("subtract-assign another vec2 to it") {
			u -= vec2(0.0f, 2.0f);
			THEN("the coordinates of the first vec2 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 0.0f);
			}
		}
		WHEN("multiply-assign a number to it") {
			u *= 3.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 9.0f);
				REQUIRE(u.getY() == 6.0f);
			}
		}
		WHEN("divide-assign a number to it") {
			u /= 10.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 0.3f);
				REQUIRE(u.getY() == 0.2f);
			}
		}
	}
}


SCENARIO("vec2 can be compared with each other", "[vec2]") {
	GIVEN("three vec2 created in any way") {
		vec2 u = vec2(1.0f, 2.0f);
		vec2 v = vec2(1.0f, 2.0f);
		vec2 w = vec2(2.0f, 2.0f);
		WHEN("they are equal") {
			bool uveq = (u == v);
			THEN("they must be equal") {
				REQUIRE(uveq);
			}
			bool uvneq = (u != v);
			THEN("they must not be not equal") {
				REQUIRE(!uvneq);
			}
		}
		WHEN("they are not equal") {
			bool uweq = (u == w);
			THEN("they must not be equal") {
				REQUIRE(!uweq);
			}
			bool uwneq = (u != w);
			THEN("they must be not equal") {
				REQUIRE(uwneq);
			}
		}
	}
}

SCENARIO("vec2 can use some mathematical functions", "[vec2]") {
	GIVEN("a vec2 created in any way") {
		vec2 u = vec2(3.0f, 4.0f);
		WHEN("you calculate its quadrance") {
			float q = u.quadrance();
			THEN("it should be equal to the sum of its coordinates squared") {
				REQUIRE(q == 25.0f);
			}
		}
		WHEN("you calculate its norm") {
			float q = u.norm();
			THEN("it should be equal to the square root of the sum of its coordinates squared") {
				REQUIRE(q == 5.0f);
			}
		}
		WHEN("you normalize it") {
			u.normalize();
			THEN("it should end up with norm 1") {
				REQUIRE(u.norm() == 1.0f);
			}
		}
	}
	GIVEN("two vec2 created in any way") {
		vec2 u = vec2(1.0f, 2.0f);
		vec2 v = vec2(4.0f, 3.0f);
		WHEN("you calculate the dot product") {
			float f = u.dot(v);
			THEN("the result should be equal to the sum of each coordinate multiplied in pairs XX, YY") {
				REQUIRE(f == 10.0f);
			}

			WHEN("you reverse the order") {
				float f = v.dot(u);
				THEN("it should be commutative") {
					REQUIRE(f == 10.0f);
				}
			}
		}
	}
}



/*************************vec3 tests*************************_

SCENARIO("vec3 can be instantiated", "[vec3]") {
	GIVEN("A default vec3 with 0,0,0,0 coordinates") {
		vec3 v = vec3();
		REQUIRE(v.getX() == 0.0f);
		REQUIRE(v.getY() == 0.0f);
		REQUIRE(v.getZ() == 0.0f);
		WHEN("the coordinates are changed") {
			v.setX(2.0f);
			v.setY(3.0f);
			v.setZ(4.0f);
			THEN("they must be changed") {
				REQUIRE(v.getX() == 2.0f);
				REQUIRE(v.getY() == 3.0f);
				REQUIRE(v.getZ() == 4.0f);
			}
		}
	}
	GIVEN("A vec3 created with the float constructor") {
		vec3 v = vec3(1.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 1.0f);
		REQUIRE(v.getZ() == 1.0f);
	}
	GIVEN("A vec3 created with the coordinate specification constructor") {
		vec3 v = vec3(1.0f, 2.0f, 3.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 2.0f);
		REQUIRE(v.getZ() == 3.0f);
	}
	GIVEN("A vec3 created in any way") {
		vec3 v = vec3(1.0f, 2.0f, 3.0f);
		WHEN("we create a copy of this vec3") {
			vec3 v2 = vec3(v);
			THEN("the coordinates must be the same") {
				REQUIRE(v.getX() == 1.0f);
				REQUIRE(v.getY() == 2.0f);
				REQUIRE(v.getZ() == 3.0f);
			}
		}
	}
}

SCENARIO("vec3 can use operators", "[vec3]") {
	GIVEN("Two vec3 created in any way") {
		vec3 u = vec3(4.0f, 2.0f, 1.0f);
		vec3 v = vec3(3.0f, 3.0f, 2.0f);
		WHEN("add one to the other") {
			vec3 w = u + v;
			THEN("the coordinates of the resulting vec3 must be correct") {
				REQUIRE(w.getX() == 7.0f);
				REQUIRE(w.getY() == 5.0f);
				REQUIRE(w.getZ() == 3.0f);
			}
			WHEN("we reverse the order") {
				vec3 z = v + u;
				THEN("the addition must be commutative") {
					REQUIRE(w.getX() == 7.0f);
					REQUIRE(w.getY() == 5.0f);
					REQUIRE(w.getZ() == 3.0f);
				}
			}
		}
		WHEN("subtract one to the other") {
			vec3 w = u - v;
			THEN("the coordinates of the resulting vec3 must be correct") {
				REQUIRE(w.getX() == 1.0f);
				REQUIRE(w.getY() == -1.0f);
				REQUIRE(w.getZ() == -1.0f);
			}
			WHEN("we reverse the order") {
				vec3 z = v - u;
				THEN("the subtraction must not be commutative") {
					REQUIRE(z.getX() == -1.0f);
					REQUIRE(z.getY() == 1.0f);
					REQUIRE(z.getZ() == 1.0f);
				}
			}
		}
		WHEN("multiply one of them by a scalar") {
			vec3 w = u * 3.0f;
			THEN("the coordinates of the resulting vec3 must be correct") {
				REQUIRE(w.getX() == 12.0f);
				REQUIRE(w.getY() == 6.0f);
				REQUIRE(w.getZ() == 3.0f);
			}
			WHEN("we reverse the order") {
				vec3 z = 3.0f * u;
				THEN("the multiplication must be commutative") {
					REQUIRE(w.getX() == 12.0f);
					REQUIRE(w.getY() == 6.0f);
					REQUIRE(w.getZ() == 3.0f);
				}
			}
		}
		WHEN("divide one of them by a scalar") {
			vec3 w = u / 10.0f;
			THEN("the coordinates of the resulting vec3 must be correct") {
				REQUIRE(w.getX() == 0.4f);
				REQUIRE(w.getY() == 0.2f);
				REQUIRE(w.getZ() == 0.1f);
			}
		}
	}
	GIVEN("A vec3 created in any way") {
		vec3 u = vec3(3.0f, 2.0f, 1.0f);
		WHEN("assign another vec3 to it") {
			u = vec3(0.0f, 2.0f, 2.0f);
			THEN("the coordinates of the first vec3 must be changed") {
				REQUIRE(u.getX() == 0.0f);
				REQUIRE(u.getY() == 2.0f);
				REQUIRE(u.getZ() == 2.0f);
			}
		}
		WHEN("add-assign another vec3 to it") {
			u += vec3(0.0f, 2.0f, 2.0f);
			THEN("the coordinates of the first vec3 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 4.0f);
				REQUIRE(u.getZ() == 3.0f);
			}
		}
		WHEN("subtract-assign another vec3 to it") {
			u -= vec3(0.0f, 2.0f, 2.0f);
			THEN("the coordinates of the first vec3 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 0.0f);
				REQUIRE(u.getZ() == -1.0f);
			}
		}
		WHEN("multiply-assign a number to it") {
			u *= 3.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 9.0f);
				REQUIRE(u.getY() == 6.0f);
				REQUIRE(u.getZ() == 3.0f);
			}
		}
		WHEN("divide-assign a number to it") {
			u /= 10.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 0.3f);
				REQUIRE(u.getY() == 0.2f);
				REQUIRE(u.getZ() == 0.1f);
			}
		}
	}
}


SCENARIO("vec3 can be compared with each other", "[vec3]") {
	GIVEN("three vec3 created in any way") {
		vec3 u = vec3(1.0f, 2.0f, 2.0f);
		vec3 v = vec3(1.0f, 2.0f, 2.0f);
		vec3 w = vec3(2.0f, 2.0f, 2.0f);
		WHEN("they are equal") {
			bool uveq = (u == v);
			THEN("they must be equal") {
				REQUIRE(uveq);
			}
			bool uvneq = (u != v);
			THEN("they must not be not equal") {
				REQUIRE(!uvneq);
			}
		}
		WHEN("they are not equal") {
			bool uweq = (u == w);
			THEN("they must not be equal") {
				REQUIRE(!uweq);
			}
			bool uwneq = (u != w);
			THEN("they must be not equal") {
				REQUIRE(uwneq);
			}
		}
	}
}

SCENARIO("vec3 can use some mathematical functions", "[vec3]") {
	GIVEN("a vec3 created in any way") {
		vec3 u = vec3(2.0f, 4.0f, 4.0f);
		WHEN("you calculate its quadrance") {
			float q = u.quadrance();
			THEN("it should be equal to the sum of its coordinates squared") {
				REQUIRE(q == 36.0f);
			}
		}
		WHEN("you calculate its norm") {
			float q = u.norm();
			THEN("it should be equal to the square root of the sum of its coordinates squared") {
				REQUIRE(q == 6.0f);
			}
		}
		WHEN("you normalize it") {
			u.normalize();
			THEN("it should end up with norm 1") {
				REQUIRE(u.norm() == 1.0f);
			}
		}
	}
	GIVEN("two vec3 created in any way") {
		vec3 u = vec3(1.0f, 2.0f, 3.0f);
		vec3 v = vec3(4.0f, 3.0f, 2.0f);
		WHEN("you calculate the dot product") {
			float f = u.dot(v);
			THEN("the result should be equal to the sum of each coordinate multiplied in pairs XX, YY, ZZ") {
				REQUIRE(f == 16.0f);
			}

			WHEN("you reverse the order") {
				float f = v.dot(u);
				THEN("it should be commutative") {
					REQUIRE(f == 16.0f);
				}
			}
		}
		WHEN("you calculate the cross product") {
			vec3 w = u.cross(v);
			THEN("the result should be a vector perpendicular to the plane created by them") {
				REQUIRE(w.getX() == -5.0f);
				REQUIRE(w.getY() == 10.0f);
				REQUIRE(w.getZ() == -5.0f);
			}

			WHEN("you reverse the order") {
				vec3 w = v.cross(u);
				THEN("it should not be commutative") {
					REQUIRE(w.getX() == 5.0f);
					REQUIRE(w.getY() == -10.0f);
					REQUIRE(w.getZ() == 5.0f);
				}
			}
		}
		WHEN("you rotate the first around the second using the rodrigue's formula") {
			vec3 v1 = vec3(1, 0, 0);
			vec3 v2 = vec3(0, 2, 0);
			vec3 v3 = vec3(0, 0, 3);
			REQUIRE(v1.rodrigues(v1, 90.0f).clean() == vec3(1.0f, 0.0f, 0.0f));
			REQUIRE(v1.rodrigues(v2, 90.0f).clean() == vec3(0.0f, 0.0f, -1.0f));
			REQUIRE(v1.rodrigues(v3, 90.0f).clean() == vec3(0.0f, 1.0f, 0.0f));
			REQUIRE(v2.rodrigues(v1, 90.0f).clean() == vec3(0.0f, 0.0f, 2.0f));
			REQUIRE(v2.rodrigues(v2, 90.0f).clean() == vec3(0.0f, 2.0f, 0.0f));
			REQUIRE(v2.rodrigues(v3, 90.0f).clean() == vec3(-2.0f, 0.0f, 0.0f));
			REQUIRE(v3.rodrigues(v1, 90.0f).clean() == vec3(0.0f, -3.0f, 0.0f));
			REQUIRE(v3.rodrigues(v2, 90.0f).clean() == vec3(3.0f, 0.0f, 0.0f));
			REQUIRE(v3.rodrigues(v3, 90.0f).clean() == vec3(0.0f, 0.0f, 3.0f));

		}
	}
}


/*************************vec4 tests*************************_

SCENARIO("vec4 can be instantiated", "[vec4]") {
	GIVEN("A default vec4 with 0,0,0,0 coordinates") {
		vec4 v = vec4();
		REQUIRE(v.getX() == 0.0f);
		REQUIRE(v.getY() == 0.0f);
		REQUIRE(v.getZ() == 0.0f);
		REQUIRE(v.getW() == 0.0f);
		WHEN("the coordinates are changed") {
			v.setX(2.0f);
			v.setY(3.0f);
			v.setZ(4.0f);
			v.setW(5.0f);
			THEN("they must be changed") {
				REQUIRE(v.getX() == 2.0f);
				REQUIRE(v.getY() == 3.0f);
				REQUIRE(v.getZ() == 4.0f);
				REQUIRE(v.getW() == 5.0f);
			}
		}
	}
	GIVEN("A vec4 created with the float constructor") {
		vec4 v = vec4(1.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 1.0f);
		REQUIRE(v.getZ() == 1.0f);
		REQUIRE(v.getW() == 1.0f);
	}
	GIVEN("A vec4 created with the coordinate specification constructor") {
		vec4 v = vec4(1.0f, 2.0f, 3.0f, 4.0f);
		REQUIRE(v.getX() == 1.0f);
		REQUIRE(v.getY() == 2.0f);
		REQUIRE(v.getZ() == 3.0f);
		REQUIRE(v.getW() == 4.0f);
	}
	GIVEN("A vec4 created in any way") {
		vec4 v = vec4(1.0f, 2.0f, 3.0f, 0.0f);
		WHEN("we create a copy of this vec4") {
			vec4 v2 = vec4(v);
			THEN("the coordinates must be the same") {
				REQUIRE(v.getX() == 1.0f);
				REQUIRE(v.getY() == 2.0f);
				REQUIRE(v.getZ() == 3.0f);
				REQUIRE(v.getW() == 0.0f);
			}
		}
	}
}

SCENARIO("vec4 can use operators", "[vec4]") {
	GIVEN("Two vec4 created in any way") {
		vec4 u = vec4(4.0f, 2.0f, 1.0f, 5.0f);
		vec4 v = vec4(3.0f, 3.0f, 2.0f, 3.0f);
		WHEN("add one to the other") {
			vec4 w = u + v;
			THEN("the coordinates of the resulting vec4 must be correct") {
				REQUIRE(w.getX() == 7.0f);
				REQUIRE(w.getY() == 5.0f);
				REQUIRE(w.getZ() == 3.0f);
				REQUIRE(w.getW() == 8.0f);
			}
			WHEN("we reverse the order") {
				vec4 z = v + u;
				THEN("the addition must be commutative") {
					REQUIRE(w.getX() == 7.0f);
					REQUIRE(w.getY() == 5.0f);
					REQUIRE(w.getZ() == 3.0f);
					REQUIRE(w.getW() == 8.0f);
				}
			}
		}
		WHEN("subtract one to the other") {
			vec4 w = u - v;
			THEN("the coordinates of the resulting vec4 must be correct") {
				REQUIRE(w.getX() == 1.0f);
				REQUIRE(w.getY() == -1.0f);
				REQUIRE(w.getZ() == -1.0f);
				REQUIRE(w.getW() == 2.0f);
			}
			WHEN("we reverse the order") {
				vec4 z = v - u;
				THEN("the subtraction must not be commutative") {
					REQUIRE(z.getX() == -1.0f);
					REQUIRE(z.getY() == 1.0f);
					REQUIRE(z.getZ() == 1.0f);
					REQUIRE(z.getW() == -2.0f);
				}
			}
		}
		WHEN("multiply one of them by a scalar") {
			vec4 w = u * 3.0f;
			THEN("the coordinates of the resulting vec4 must be correct") {
				REQUIRE(w.getX() == 12.0f);
				REQUIRE(w.getY() == 6.0f);
				REQUIRE(w.getZ() == 3.0f);
				REQUIRE(w.getW() == 15.0f);
			}
			WHEN("we reverse the order") {
				vec4 z = 3.0f * u;
				THEN("the multiplication must be commutative") {
					REQUIRE(w.getX() == 12.0f);
					REQUIRE(w.getY() == 6.0f);
					REQUIRE(w.getZ() == 3.0f);
					REQUIRE(w.getW() == 15.0f);
				}
			}
		}
		WHEN("divide one of them by a scalar") {
			vec4 w = u / 10.0f;
			THEN("the coordinates of the resulting vec4 must be correct") {
				REQUIRE(w.getX() == 0.4f);
				REQUIRE(w.getY() == 0.2f);
				REQUIRE(w.getZ() == 0.1f);
				REQUIRE(w.getW() == 0.5f);
			}
		}
	}
	GIVEN("A vec4 created in any way") {
		vec4 u = vec4(3.0f, 2.0f, 1.0f, 5.0f);
		WHEN("assign another vec4 to it") {
			u = vec4(0.0f, 2.0f, 2.0f, -1.0f);
			THEN("the coordinates of the first vec4 must be changed") {
				REQUIRE(u.getX() == 0.0f);
				REQUIRE(u.getY() == 2.0f);
				REQUIRE(u.getZ() == 2.0f);
				REQUIRE(u.getW() == -1.0f);
			}
		}
		WHEN("add-assign another vec4 to it") {
			u += vec4(0.0f, 2.0f, 2.0f, -1.0f);
			THEN("the coordinates of the first vec4 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 4.0f);
				REQUIRE(u.getZ() == 3.0f);
				REQUIRE(u.getW() == 4.0f);
			}
		}
		WHEN("subtract-assign another vec4 to it") {
			u -= vec4(0.0f, 2.0f, 2.0f, -1.0f);
			THEN("the coordinates of the first vec4 must be changed") {
				REQUIRE(u.getX() == 3.0f);
				REQUIRE(u.getY() == 0.0f);
				REQUIRE(u.getZ() == -1.0f);
				REQUIRE(u.getW() == 6.0f);
			}
		}
		WHEN("multiply-assign a number to it") {
			u *= 3.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 9.0f);
				REQUIRE(u.getY() == 6.0f);
				REQUIRE(u.getZ() == 3.0f);
				REQUIRE(u.getW() == 15.0f);
			}
		}
		WHEN("divide-assign a number to it") {
			u /= 10.0f;
			THEN("its coordinates must be changed") {
				REQUIRE(u.getX() == 0.3f);
				REQUIRE(u.getY() == 0.2f);
				REQUIRE(u.getZ() == 0.1f);
				REQUIRE(u.getW() == 0.5);
			}
		}
	}
}


SCENARIO("vec4 can be compared with each other", "[vec4]") {
	GIVEN("three vec4 created in any way") {
		vec4 u = vec4(1.0f, 2.0f, 2.0f, 1.0f);
		vec4 v = vec4(1.0f, 2.0f, 2.0f, 1.0f);
		vec4 w = vec4(2.0f, 2.0f, 2.0f, 1.0f);
		WHEN("they are equal") {
			bool uveq = (u == v);
			THEN("they must be equal") {
				REQUIRE(uveq);
			}
			bool uvneq = (u != v);
			THEN("they must not be not equal") {
				REQUIRE(!uvneq);
			}
		}
		WHEN("they are not equal") {
			bool uweq = (u == w);
			THEN("they must not be equal") {
				REQUIRE(!uweq);
			}
			bool uwneq = (u != w);
			THEN("they must be not equal") {
				REQUIRE(uwneq);
			}
		}
	}
}

SCENARIO("vec4 can use some mathematical functions", "[vec4]") {
	GIVEN("a vec4 created in any way") {
		vec4 u = vec4(1.0f, 1.0f, 3.0f, 5.0f);
		WHEN("you calculate its quadrance") {
			float q = u.quadrance();
			THEN("it should be equal to the sum of its coordinates squared") {
				REQUIRE(q == 36.0f);
			}
		}
		WHEN("you calculate its norm") {
			float q = u.norm();
			THEN("it should be equal to the square root of the sum of its coordinates squared") {
				REQUIRE(q == 6.0f);
			}
		}
		WHEN("you normalize it") {
			u.normalize();
			THEN("it should end up with norm 1") {
				REQUIRE(u.norm() == 1.0f);
			}
		}
	}
	GIVEN("two vec4 created in any way") {
		vec4 u = vec4(1.0f, 2.0f, 3.0f, 4.0f);
		vec4 v = vec4(4.0f, 3.0f, 2.0f, 1.0f);
		WHEN("you calculate the dot product") {
			float f = u.dot(v);
			THEN("the result should be equal to the sum of each coordinate multiplied in pairs XX, YY, ZZ, WW") {
				REQUIRE(f == 20.0f);
			}

			WHEN("you reverse the order") {
				float f = v.dot(u);
				THEN("it should be commutative") {
					REQUIRE(f == 20.0f);
				}
			}
		}
	}
}

/*************************mat2 tests*************************_

SCENARIO("mat2 can be instantiated", "[mat2]") {
	GIVEN("a mat2 created with the coordinate specification constructor") {
		mat2 m = mat2(1.0f, 2.0f,
			3.0f, 4.0f);
		REQUIRE(m.getCoordinate(0, 0) == 1.0f);
		REQUIRE(m.getCoordinate(0, 1) == 2.0f);
		REQUIRE(m.getCoordinate(1, 0) == 3.0f);
		REQUIRE(m.getCoordinate(1, 1) == 4.0f);
	}
	GIVEN("a mat2 created in any way") {
		mat2 m = mat2(1.0f, 2.0f,
			3.0f, 4.0f);
		WHEN("we create a copy of this mat2") {
			mat2 m2 = mat2(m);
			THEN("the coordinates must be the same") {
				REQUIRE(m2.getCoordinate(0, 0) == 1.0f);
				REQUIRE(m2.getCoordinate(0, 1) == 2.0f);
				REQUIRE(m2.getCoordinate(1, 0) == 3.0f);
				REQUIRE(m2.getCoordinate(1, 1) == 4.0f);
			}
			THEN("the == operator must confirm they're equal") {
				REQUIRE(m == m2);
			}
			THEN("the != operator negated must confirm they're equal") {
				REQUIRE(!(m != m2));
			}
		}
	}
	GIVEN("a mat3 created in any way") {
		mat3 m = mat3::identityMatrix();
		THEN("a mat2 created from it, must have the 4 top left coordinates") {
			REQUIRE(mat2(m) == mat2(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	GIVEN("a mat4 created in any way") {
		mat4 m = mat4::identityMatrix();
		THEN("a mat2 created from it, must have the 4 top left coordinates") {
			REQUIRE(mat2(m) == mat2(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

SCENARIO("creation of special mat2 matrices must be simple", "[mat2]") {
	GIVEN("identity matrix") {
		REQUIRE(mat2::identityMatrix() == mat2(1.0f, 0.0f, 0.0f, 1.0f));
	}
	GIVEN("rotation matrix") {
		REQUIRE(mat2::rotationMatrix(90).clean() == mat2(0.0f, -1.0f, 1.0f, 0.0f));
	}
	GIVEN("scale matrix") {
		REQUIRE(mat2::scaleMatrix(2) == mat2(2.0f, 0.0f, 0.0f, 2.0f));
	}
	GIVEN("scale matrix") {
		REQUIRE(mat2::scaleMatrix(vec2(1.0f, 2.0f)) == mat2(1.0f, 0.0f, 0.0f, 2.0f));
	}
}

SCENARIO("mat2 can use operators", "[mat2]") {
	GIVEN("two mat2 created in any way") {
		mat2 m = mat2(1.0f, 2.0f,
			3.0f, 4.0f);
		mat2 n = mat2(4.0f, 3.0f,
			2.0f, 1.0f);
		THEN("add them") {
			REQUIRE((m + n) == mat2(5.0f, 5.0f, 5.0f, 5.0f));
			REQUIRE((n + m) == mat2(5.0f, 5.0f, 5.0f, 5.0f));
		}
		THEN("subtract them") {
			REQUIRE((m - n) == mat2(-3.0f, -1.0f, 1.0f, 3.0f));
			REQUIRE((n - m) == mat2(3.0f, 1.0f, -1.0f, -3.0f));
		}
		THEN("multiply them") {
			REQUIRE((m * n) == mat2(8.0f, 5.0f, 20.0f, 13.0f));
			REQUIRE((n * m) == mat2(13.0f, 20.0f, 5.0f, 8.0f));
		}
		THEN("multiply by a scalar") {
			REQUIRE((2 * m) == mat2(2.0f, 4.0f, 6.0f, 8.0f));
			REQUIRE((m * 2) == mat2(2.0f, 4.0f, 6.0f, 8.0f));
		}
		THEN("multiply by a vec2") {
			REQUIRE((m * vec2(1.0f, 0.0f)) == vec2(1.0f, 3.0f));
		}
	}
}


SCENARIO("mat2 can use math", "[mat2]") {
	GIVEN("a mat2 created in any way") {
		mat2 m = mat2(1.0f, 2.0f,
			3.0f, 4.0f);
		THEN("transpose it") {
			REQUIRE(mat2::transpose(m) == mat2(1.0f, 3.0f, 2.0f, 4.0f));
		}
		THEN("get its determinant") {
			REQUIRE(m.determinant() == -2.0f);
		}
		THEN("get its inverse") {
			REQUIRE(mat2::inverse(m).clean() == mat2(-2.0f, 1.0f, 1.5f, -0.5f));
		}
	}
}




/*************************mat3 tests*************************_

SCENARIO("mat3 can be instantiated", "[mat3]") {
	GIVEN("a mat3 created with the coordinate specification constructor") {
		mat3 m = mat3(1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f);
		REQUIRE(m.getCoordinate(0, 0) == 1.0f);
		REQUIRE(m.getCoordinate(0, 1) == 2.0f);
		REQUIRE(m.getCoordinate(0, 2) == 3.0f);
		REQUIRE(m.getCoordinate(1, 0) == 4.0f);
		REQUIRE(m.getCoordinate(1, 1) == 5.0f);
		REQUIRE(m.getCoordinate(1, 2) == 6.0f);
		REQUIRE(m.getCoordinate(2, 0) == 7.0f);
		REQUIRE(m.getCoordinate(2, 1) == 8.0f);
		REQUIRE(m.getCoordinate(2, 2) == 9.0f);
	}
	GIVEN("a mat3 created in any way") {
		mat3 m = mat3(1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f);
		WHEN("we create a copy of this mat3") {
			mat3 m2 = mat3(m);
			THEN("the coordinates must be the same") {
				REQUIRE(m2.getCoordinate(0, 0) == 1.0f);
				REQUIRE(m2.getCoordinate(0, 1) == 2.0f);
				REQUIRE(m2.getCoordinate(0, 2) == 3.0f);
				REQUIRE(m2.getCoordinate(1, 0) == 4.0f);
				REQUIRE(m2.getCoordinate(1, 1) == 5.0f);
				REQUIRE(m2.getCoordinate(1, 2) == 6.0f);
				REQUIRE(m2.getCoordinate(2, 0) == 7.0f);
				REQUIRE(m2.getCoordinate(2, 1) == 8.0f);
				REQUIRE(m2.getCoordinate(2, 2) == 9.0f);
			}
			THEN("the == operator must confirm they're equal") {
				REQUIRE(m == m2);
			}
			THEN("the != operator negated must confirm they're equal") {
				REQUIRE(!(m != m2));
			}
		}
	}
	GIVEN("a mat2 created in any way") {
		mat2 m = mat2::identityMatrix();
		THEN("a mat3 created from it, must have the 4 top left coordinates") {
			REQUIRE(mat3(m) == mat3(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f));
		}
	}
	GIVEN("a mat4 created in any way") {
		mat4 m = mat4::identityMatrix();
		THEN("a mat3 created from it, must have the 6 top left coordinates") {
			REQUIRE(mat3(m) == mat3(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f));
		}
	}
}

SCENARIO("creation of special mat3 matrices must be simple", "[mat3]") {
	GIVEN("identity matrix") {
		REQUIRE(mat3::identityMatrix() == mat3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f));
	}
	GIVEN("rotation matrix") {
		REQUIRE(mat3::xRotationMatrix(90).clean() == mat3(
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 1.0f, 0.0f));
		REQUIRE(mat3::yRotationMatrix(90).clean() == mat3(
			0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f));
		REQUIRE(mat3::zRotationMatrix(90).clean() == mat3(
			0.0f, -1.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f));

	}
	GIVEN("scale matrix") {
		REQUIRE(mat3::scaleMatrix(2) == mat3(
			2.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 2.0f));
	}
	GIVEN("scale matrix") {
		REQUIRE(mat3::scaleMatrix(vec3(1.0f, 2.0f, 3.0f)) == mat3(
			1.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 3.0f));
	}
	GIVEN("translation matrix") {
		REQUIRE(mat3::translationMatrix(vec2(1.0f, 2.0f)) == mat3(
			1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 2.0f,
			0.0f, 0.0f, 1.0f));
	}
}

SCENARIO("mat3 can use operators", "[mat3]") {
	GIVEN("two mat3 created in any way") {
		mat3 m = mat3(1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f);
		mat3 n = mat3(9.0f, 8.0f, 7.0f,
			6.0f, 5.0f, 4.0f,
			3.0f, 2.0f, 1.0f);
		THEN("add them") {
			REQUIRE((m + n) == mat3(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f));
			REQUIRE((n + m) == mat3(10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f));
		}
		THEN("subtract them") {
			REQUIRE((m - n) == mat3(-8.0f, -6.0f, -4.0f, -2.0f, 0.0f, 2.0f, 4.0f, 6.0f, 8.0f));
			REQUIRE((n - m) == mat3(8.0f, 6.0f, 4.0f, 2.0f, 0.0f, -2.0f, -4.0f, -6.0f, -8.0f));
		}
		THEN("multiply them") {
			REQUIRE((m * n) == mat3(30.0f, 24.0f, 18.0f, 84.0f, 69.0f, 54.0f, 138.0f, 114.0f, 90.0f));
			REQUIRE((n * m) == mat3(90.0f, 114.0f, 138.0f, 54.0f, 69.0f, 84.0f, 18.0f, 24.0f, 30.0f));
		}
		THEN("multiply by a scalar") {
			REQUIRE((2 * m) == mat3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
			REQUIRE((m * 2) == mat3(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f));
		}
		THEN("multiply by a vec3") {
			REQUIRE((m * vec3(1.0f, 2.0f, 0.0f)) == vec3(5.0f, 14.0f, 23.0f));
		}
	}
}


SCENARIO("mat3 can use math", "[mat3]") {
	GIVEN("a mat3 created in any way") {
		mat3 m = mat3(1.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 2.0f, 4.0f);
		THEN("transpose it") {
			REQUIRE(mat3::transpose(m) == mat3(
				1.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 2.0f,
				0.0f, 0.0f, 4.0f));
		}
		THEN("get its determinant") {
			REQUIRE(m.determinant() == 8.0f);
		}
		THEN("get its inverse") {
			REQUIRE(mat3::inverse(m).clean() == mat3(
				1.0f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f,
				0.0f, -0.25f, 0.25f));
		}
	}
}





/*************************mat4 tests*************************_

SCENARIO("mat4 can be instantiated", "[mat4]") {
	GIVEN("a mat4 created with the coordinate specification constructor") {
		mat4 m = mat4(
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f);
		REQUIRE(m.getCoordinate(0, 0) == 1.0f);
		REQUIRE(m.getCoordinate(0, 1) == 2.0f);
		REQUIRE(m.getCoordinate(0, 2) == 3.0f);
		REQUIRE(m.getCoordinate(0, 3) == 4.0f);
		REQUIRE(m.getCoordinate(1, 0) == 5.0f);
		REQUIRE(m.getCoordinate(1, 1) == 6.0f);
		REQUIRE(m.getCoordinate(1, 2) == 7.0f);
		REQUIRE(m.getCoordinate(1, 3) == 8.0f);
		REQUIRE(m.getCoordinate(2, 0) == 9.0f);
		REQUIRE(m.getCoordinate(2, 1) == 10.0f);
		REQUIRE(m.getCoordinate(2, 2) == 11.0f);
		REQUIRE(m.getCoordinate(2, 3) == 12.0f);
		REQUIRE(m.getCoordinate(3, 0) == 13.0f);
		REQUIRE(m.getCoordinate(3, 1) == 14.0f);
		REQUIRE(m.getCoordinate(3, 2) == 15.0f);
		REQUIRE(m.getCoordinate(3, 3) == 16.0f);
	}
	GIVEN("a mat4 created in any way") {
		mat4 m = mat4(
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f);
		WHEN("we create a copy of this mat4") {
			mat4 m2 = mat4(m);
			THEN("the coordinates must be the same") {
				REQUIRE(m2.getCoordinate(0, 0) == 1.0f);
				REQUIRE(m2.getCoordinate(0, 1) == 2.0f);
				REQUIRE(m2.getCoordinate(0, 2) == 3.0f);
				REQUIRE(m2.getCoordinate(0, 3) == 4.0f);
				REQUIRE(m2.getCoordinate(1, 0) == 5.0f);
				REQUIRE(m2.getCoordinate(1, 1) == 6.0f);
				REQUIRE(m2.getCoordinate(1, 2) == 7.0f);
				REQUIRE(m2.getCoordinate(1, 3) == 8.0f);
				REQUIRE(m2.getCoordinate(2, 0) == 9.0f);
				REQUIRE(m2.getCoordinate(2, 1) == 10.0f);
				REQUIRE(m2.getCoordinate(2, 2) == 11.0f);
				REQUIRE(m2.getCoordinate(2, 3) == 12.0f);
				REQUIRE(m2.getCoordinate(3, 0) == 13.0f);
				REQUIRE(m2.getCoordinate(3, 1) == 14.0f);
				REQUIRE(m2.getCoordinate(3, 2) == 15.0f);
				REQUIRE(m2.getCoordinate(3, 3) == 16.0f);
			}
			THEN("the == operator must confirm they're equal") {
				REQUIRE(m == m2);
			}
			THEN("the != operator negated must confirm they're equal") {
				REQUIRE(!(m != m2));
			}
		}
	}
	GIVEN("a mat2 created in any way") {
		mat2 m = mat2::identityMatrix();
		THEN("a mat4 created from it, must have the 4 top left coordinates") {
			REQUIRE(mat4(m) == mat4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	GIVEN("a mat3 created in any way") {
		mat3 m = mat3::identityMatrix();
		THEN("a mat4 created from it, must have the 6 top left coordinates") {
			REQUIRE(mat4(m) == mat4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

SCENARIO("creation of special mat4 matrices must be simple", "[mat4]") {
	GIVEN("identity matrix") {
		REQUIRE(mat4::identityMatrix() == mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
	}
	GIVEN("rotation matrix") {
		REQUIRE(mat4::xRotationMatrix(90).clean() == mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
		REQUIRE(mat4::yRotationMatrix(90).clean() == mat4(
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
		REQUIRE(mat4::zRotationMatrix(90).clean() == mat4(
			0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));

	}
	GIVEN("scale matrix") {
		REQUIRE(mat4::scaleMatrix(2) == mat4(
			2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
	}
	GIVEN("scale matrix") {
		REQUIRE(mat4::scaleMatrix(vec3(1.0f, 2.0f, 3.0f)) == mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 3.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
	}
	GIVEN("translation matrix") {
		REQUIRE(mat4::translationMatrix(vec3(1.0f, 2.0f, 3.0f)) == mat4(
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 2.0f,
			0.0f, 0.0f, 1.0f, 3.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
	}
}

SCENARIO("mat4 can use operators", "[mat4]") {
	GIVEN("two mat4 created in any way") {
		mat4 m = mat4(
			1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f);
		mat4 n = mat4(
			16.0f, 15.0f, 14.0f, 13.0f,
			12.0f, 11.0f, 10.0f, 9.0f,
			8.0f, 7.0f, 6.0f, 5.0f,
			4.0f, 3.0f, 2.0f, 1.0f);
		THEN("add them") {
			REQUIRE((m + n) == mat4(17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f));
			REQUIRE((n + m) == mat4(17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f, 17.0f));
		}
		THEN("subtract them") {
			REQUIRE((m - n) == mat4(-15.0f, -13.0f, -11.0f, -9.0f, -7.0f, -5.0f, -3.0f, -1.0f, 1.0f, 3.0f, 5.0f, 7.0f, 9.0f, 11.0f, 13.0f, 15.0f));
			REQUIRE((n - m) == mat4(15.0f, 13.0f, 11.0f, 9.0f, 7.0f, 5.0f, 3.0f, 1.0f, -1.0f, -3.0f, -5.0f, -7.0f, -9.0f, -11.0f, -13.0f, -15.0f));
		}
		THEN("multiply them") {
			REQUIRE((m * n) == mat4(80.0f, 70.0f, 60.0f, 50.0f, 240.0f, 214.0f, 188.0f, 162.0f, 400.0f, 358.0f, 316.0f, 274.0f, 560.0f, 502.0f, 444.0f, 386.0f));
			REQUIRE((n * m) == mat4(386.0f, 444.0f, 502.0f, 560.0f, 274.0f, 316.0f, 358.0f, 400.0f, 162.0f, 188.0f, 214.0f, 240.0f, 50.0f, 60.0f, 70.0f, 80.0f));
		}
		THEN("multiply by a scalar") {
			REQUIRE((2 * m) == mat4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
			REQUIRE((m * 2) == mat4(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f));
		}
		THEN("multiply by a vec4") {
			REQUIRE((m * vec4(1.0f, 0.0f, 2.0f, 0.0f)) == vec4(7.0f, 19.0f, 31.0f, 43.0f));
		}
	}
}


SCENARIO("mat4 can use math", "[mat4]") {
	GIVEN("a mat4 created in any way") {
		mat4 m = mat4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 4.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f);
		THEN("transpose it") {
			REQUIRE(mat4::transpose(m) == mat4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 4.0f, 1.0f,
				0.0f, 0.0f, 0.0f, 1.0f));
		}
		THEN("get its determinant") {
			REQUIRE(m.determinant() == 8.0f);
		}
		THEN("get its inverse") {
			REQUIRE(mat4::inverse(m).clean() == mat4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f, 0.0f,
				0.0f, -0.25f, 0.25f, 0.0f,
				0.0f, 0.25f, -0.25f, 1.0f));
		}
	}
}



SCENARIO("mat4 model and normal matrix", "[mat4]") {
	GIVEN("translation matrix") {
		mat4 t = mat4::translationMatrix(vec3(1.0f, 0.0f, 0.0f));
		GIVEN("rotation matrix") {
			mat4 r = mat4::yRotationMatrix(90.0f);
			GIVEN("scale matrix") {
				mat4 s = mat4::scaleMatrix(2.0f);
				THEN("make a model matrix from it") {
					mat4 m = t*r*s;
					cout << "Model matrix: \n" << m.clean() << '\n';
					THEN("make a normal matrix from it") {
						mat3 n = mat3::transpose(mat3::inverse(mat3(m)));
						cout << "Normal matrix: \n" << n.clean() << '\n';
						THEN("multiply them by vectors") {
							vec3 v = vec3(m * vec4(vec3(0.5,0,0)), true);
							cout << "Vector by model: \n" << v.clean() << '\n';
							vec3 u = n * vec3(0, 1, 0);
							cout << "Vector by normal: \n" << u.clean() << '\n';
						}
					}
				}
			}
		}
	}
}
*/