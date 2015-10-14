#if 0
#include <test/test-models/good/variational/multivar_constraint.hpp>
#include <stan/variational/advi.hpp>
#include <gtest/gtest.h>
#include <test/unit/util.hpp>
#include <vector>
#include <string>
#include <boost/random/additive_combine.hpp> // L'Ecuyer RNG

typedef boost::ecuyer1988 rng_t;
typedef multivar_constraint_model_namespace::multivar_constraint_model Model;

TEST(advi_test, elbo_multivar_constraint_fullrank) {
  // Create mock data_var_context
  static const std::string DATA = "";
  std::stringstream data_stream(DATA);
  stan::io::dump dummy_context(data_stream);

  Model my_model(dummy_context);
  rng_t base_rng(0);
  int n_monte_carlo_grad = 10;
  int n_monte_carlo_elbo = 1e6;
  std::ostream* print_stream = &std::cout;
  Eigen::VectorXd cont_params = Eigen::VectorXd::Zero(2);
  cont_params(0) = 0.75;
  cont_params(1) = 0.75;

  stan::variational::advi<Model, stan::variational::normal_fullrank, rng_t>
    test_advi(my_model,
              cont_params,
              base_rng,
              n_monte_carlo_grad,
              n_monte_carlo_elbo,
              0.1,
              100,
              1,
              print_stream,
              &std::cout,
              &std::cout);

  // Create arbitrary variational family to calculate ELBO
  Eigen::VectorXd mu     = Eigen::VectorXd::Constant(my_model.num_params_r(),
                                                      log(2.5));
  Eigen::MatrixXd L_chol = Eigen::MatrixXd::Identity(my_model.num_params_r(),
                                                     my_model.num_params_r());
  // TODO this doesn't exist anymore
  stan::variational::normal_fullrank muL =
    stan::variational::normal_fullrank(mu, L_chol);

  double elbo = 0.0;
  elbo = test_advi.calc_ELBO(muL);

  // Calculate ELBO analytically
  double zeta = -0.5 * ( 3*2*log(2.0*stan::math::pi()) + 18.5 + 25 + 13 );
  Eigen::VectorXd mu_J = Eigen::VectorXd::Zero(2);
  mu_J(0) = 10.5;
  mu_J(1) =  7.5;

  double elbo_true = 0.0;
  elbo_true += zeta;
  elbo_true += 74.192457181505773; // mu_J.dot( (mu + 0.5).exp() );
  elbo_true += -0.5 * 3 * ( 92.363201236633131 );
  elbo_true += 2*log(2.5);
  elbo_true += 1 + log(2.0*stan::math::pi());

  double const EPSILON = 1.0;
  EXPECT_NEAR(elbo_true, elbo, EPSILON);
}

TEST(advi_test, elbo_multivar_constraint_meanfield) {
  // Create mock data_var_context
  static const std::string DATA = "";
  std::stringstream data_stream(DATA);
  stan::io::dump dummy_context(data_stream);

  Model my_model(dummy_context);
  rng_t base_rng(0);
  int n_monte_carlo_grad = 10;
  int n_monte_carlo_elbo = 1e6;
  std::ostream* print_stream = &std::cout;
  Eigen::VectorXd cont_params = Eigen::VectorXd::Zero(2);
  cont_params(0) = 0.75;
  cont_params(1) = 0.75;

  stan::variational::advi<Model, stan::variational::normal_meanfield, rng_t>
    test_advi(my_model,
              cont_params,
              base_rng,
              n_monte_carlo_grad,
              n_monte_carlo_elbo,
              0.1,
              100,
              1,
              print_stream,
              &std::cout,
              &std::cout);

  // Create arbitrary variational family to calculate ELBO
  Eigen::VectorXd mu  = Eigen::VectorXd::Constant(my_model.num_params_r(),
                                                     log(2.5));
  Eigen::VectorXd sigma_tilde  = Eigen::VectorXd::Constant(
                                          my_model.num_params_r(),
                                          0.0); // initializing sigma_tilde = 0
                                                // means sigma = 1
  // TODO this doesn't exist anymore
  stan::variational::normal_meanfield musigmatilde =
    stan::variational::normal_meanfield(mu, sigma_tilde);

  double elbo = 0.0;
  elbo = test_advi.calc_ELBO(musigmatilde);

  // Calculate ELBO analytically
  double zeta = -0.5 * ( 3*2*log(2.0*stan::math::pi()) + 18.5 + 25 + 13 );
  Eigen::VectorXd mu_J = Eigen::VectorXd::Zero(2);
  mu_J(0) = 10.5;
  mu_J(1) =  7.5;

  double elbo_true = 0.0;
  elbo_true += zeta;
  elbo_true += 74.192457181505773; //;mu_J.dot( (mu + 0.5).exp() );
  elbo_true += -0.5 * 3 * ( 92.363201236633131 );
  elbo_true += 2*log(2.5);
  elbo_true += 1 + log(2.0*stan::math::pi());

  double const EPSILON = 1.0;
  EXPECT_NEAR(elbo_true, elbo, EPSILON);
}
#endif
