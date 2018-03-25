typedef enum {

} artype;
typedef struct ar {

} ar;

dim  : uint8_t;
shape: uint64_t;
dtype : artype*;
data : uint8_t*;
a    : ar*;
rows : uint64_t;
cols : uint64_t;

ar* ar_new();
ar* ar_new_dim(dim);
ar* ar_new_shape(dim, shape, dtype);
ar* ar_new_data(dim, shape, dtype, data);
ar* ar_zeros(dim, shape, dtype);
ar* ar_ones(dim, shape, dtype);
ar* ar_full(dim, shape, dtype);
ar* ar_full_u8(dim, shape, value);
...
ar* ar_full_d(dim, shape, value);
ar* ar_eye(rows, dtype);
ar* ar_eye_cols(rows, cols, dtype);
ar* ar_range(start, stop, dtype);
ar* ar_range_step(start, stop, step, dtype);
ar* ar_range_num(start, stop, num, dtype);
ar* ar_range_geo(start, stop, num, dtype);
ar* ar_range_exp(start, stop, base, dtype);
ar* ar_new_diag(num, type, data);
ar* ar_new_tril(rows);
ar* ar_new_triu(rows);
ar* ar_zeros_like(a);
ar* ar_ones_like(a);
ar* ar_full_like_u8(a, value);
...
ar* ar_full_like_d(a, value);
ar* ar_diag(a);
ar* ar_tril(a);
ar* ar_triu(a);
ar* ar_new_copy(a);
ar* ar_read_csv(filename);
ar* ar_read_ncz(filename);

ar* ar_write_csv(filename);
ar* ar_write_ncz(filename);

void ar_fill(a, value);
void ar_copy(a, b);
ar* ar_flatten(a);
ar* ar_transpose(a);
ar* ar_sum(a, naxes, axes, dtype);
ar* ar_prod(a, naxes, axes, dtype);
ar* ar_mean(a, naxes, axes, dtype);
ar* ar_max(a, naxes, axes, dtype);
ar* ar_min(a, naxes, axes, dtype);
ar* ar_std(a, naxes, axes, dtype);
ar* ar_var(a, naxes, axes, dtype);
ar* ar_std(a, naxes, axes, dtype);
ar* ar_trunc(a, dtype);
ar* ar_round(a, dtype);
ar* ar_floor(a, dtype);
ar* ar_ceil(a, dtype);
ar* ar_add(a, b);
ar* ar_multiply(a, b);
ar* ar_divide(a, b);
ar* ar_subtract(a, b);
ar* ar_power(a, b);
ar* ar_negative(a, b);
ar* ar_reciprocal(a, b);
ar* ar_clip(a, min, max);
ar* ar_sqrt(a);
ar* ar_log(a);
ar* ar_exp(a);
ar* ar_sin(a);
ar* ar_cos(a);
ar* ar_tan(a);
ar* ar_asin(a);
ar* ar_acos(a);
ar* ar_atan(a);
ar* ar_rad2deg(a);
ar* ar_deg2rad(a);
ar* ar_sinh(a);
ar* ar_cosh(a);
ar* ar_tanh(a);
ar* ar_asinh(a);
ar* ar_acosh(a);
ar* ar_atanh(a);
ar* ar_sinc(a);
ar* ar_max_between(a, b);
ar* ar_min_between(a, b);

ar* ar_cross(a, b);
ar* ar_dot(a, b);
ar* ar_outer();
ar* ar_outer();
ar* ar_svd();
ar* ar_qr();
ar* ar_cholesky();
